// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "DeferredShadingRenderer.h"

#if RHI_RAYTRACING

#include "RayTracingSkyLight.h"
#include "ScenePrivate.h"
#include "SceneRenderTargets.h"
#include "RenderGraphBuilder.h"
#include "RenderTargetPool.h"
#include "RHIResources.h"
#include "UniformBuffer.h"
#include "RayGenShaderUtils.h"
#include "PathTracingUniformBuffers.h"
#include "SceneTextureParameters.h"
#include "ScreenSpaceDenoise.h"
#include "ClearQuad.h"
#include "PostProcess/PostProcessing.h"
#include "PostProcess/SceneFilterRendering.h"
#include "Raytracing/RaytracingOptions.h"
#include "BlueNoise.h"
#include "SceneTextureParameters.h"

static int32 GRayTracingGlobalIllumination = -1;
static FAutoConsoleVariableRef CVarRayTracingGlobalIllumination(
	TEXT("r.RayTracing.GlobalIllumination"),
	GRayTracingGlobalIllumination,
	TEXT("-1: Value driven by postprocess volume (default) \n")
	TEXT(" 0: ray tracing global illumination off \n")
	TEXT(" 1: ray tracing global illumination enabled")
);

static int32 GRayTracingGlobalIlluminationSamplesPerPixel = -1;
static FAutoConsoleVariableRef CVarRayTracingGlobalIlluminationSamplesPerPixel(
	TEXT("r.RayTracing.GlobalIllumination.SamplesPerPixel"),
	GRayTracingGlobalIlluminationSamplesPerPixel,
	TEXT("Samples per pixel (default = -1 (driven by postprocesing volume))")
);

static float GRayTracingGlobalIlluminationMaxRayDistance = 1.0e27;
static FAutoConsoleVariableRef CVarRayTracingGlobalIlluminationMaxRayDistance(
	TEXT("r.RayTracing.GlobalIllumination.MaxRayDistance"),
	GRayTracingGlobalIlluminationMaxRayDistance,
	TEXT("Max ray distance (default = 1.0e27)")
);

static int32 GRayTracingGlobalIlluminationMaxBounces = -1;
static FAutoConsoleVariableRef CVarRayTracingGlobalIlluminationMaxBounces(
	TEXT("r.RayTracing.GlobalIllumination.MaxBounces"),
	GRayTracingGlobalIlluminationMaxBounces,
	TEXT("Max bounces (default = -1 (driven by postprocesing volume))")
);

static int32 GRayTracingGlobalIlluminationNextEventEstimationSamples = 2;
static FAutoConsoleVariableRef CVarRayTracingGlobalIlluminationNextEventEstimationSamples(
	TEXT("r.RayTracing.GlobalIllumination.NextEventEstimationSamples"),
	GRayTracingGlobalIlluminationNextEventEstimationSamples,
	TEXT("Number of sample draws for next-event estimation (default = 2)")
	TEXT("NOTE: This parameter is experimental")
);

static float GRayTracingGlobalIlluminationDiffuseThreshold = 0.05;
static FAutoConsoleVariableRef CVarRayTracingGlobalIlluminationDiffuseThreshold(
	TEXT("r.RayTracing.GlobalIllumination.DiffuseThreshold"),
	GRayTracingGlobalIlluminationDiffuseThreshold,
	TEXT("Diffuse luminance threshold for evaluating global illumination")
	TEXT("NOTE: This parameter is experimental")
);

static int32 GRayTracingGlobalIlluminationDenoiser = 1;
static FAutoConsoleVariableRef CVarRayTracingGlobalIlluminationDenoiser(
	TEXT("r.RayTracing.GlobalIllumination.Denoiser"),
	GRayTracingGlobalIlluminationDenoiser,
	TEXT("Denoising options (default = 1)")
);

static int32 GRayTracingGlobalIlluminationEvalSkyLight = 0;
static FAutoConsoleVariableRef CVarRayTracingGlobalIlluminationEvalSkyLight(
	TEXT("r.RayTracing.GlobalIllumination.EvalSkyLight"),
	GRayTracingGlobalIlluminationEvalSkyLight,
	TEXT("Evaluate SkyLight multi-bounce contribution")
	TEXT("NOTE: This parameter is experimental")
);

static int32 GRayTracingGlobalIlluminationUseRussianRoulette = 0;
static FAutoConsoleVariableRef CVarRayTracingGlobalIlluminationUseRussianRoulette(
	TEXT("r.RayTracing.GlobalIllumination.UseRussianRoulette"),
	GRayTracingGlobalIlluminationUseRussianRoulette,
	TEXT("Perform Russian Roulette to only cast diffuse rays on surfaces with brighter albedos (default = 0)")
	TEXT("NOTE: This parameter is experimental")
);

static float GRayTracingGlobalIlluminationScreenPercentage = 50.0;
static FAutoConsoleVariableRef CVarRayTracingGlobalIlluminationScreenPercentage(
	TEXT("r.RayTracing.GlobalIllumination.ScreenPercentage"),
	GRayTracingGlobalIlluminationScreenPercentage,
	TEXT("Screen percentage for ray tracing global illumination (default = 50)")
);

static TAutoConsoleVariable<int32> CVarRayTracingGlobalIlluminationEnableTwoSidedGeometry(
	TEXT("r.RayTracing.GlobalIllumination.EnableTwoSidedGeometry"),
	1,
	TEXT("Enables two-sided geometry when tracing GI rays (default = 1)"),
	ECVF_RenderThreadSafe
);

static int32 GRayTracingGlobalIlluminationTileSize = 0;
static FAutoConsoleVariableRef CVarRayTracingGlobalIlluminationTileSize(
	TEXT("r.RayTracing.GlobalIllumination.TileSize"),
	GRayTracingGlobalIlluminationTileSize,
	TEXT("Render ray traced global illumination in NxN piel tiles, where each tile is submitted as separate GPU command buffer, allowing high quality rendering without triggering timeout detection. (default = 0, tiling disabled)")
);

static const int32 GLightCountMax = 64;

DECLARE_GPU_STAT_NAMED(RayTracingGlobalIllumination, TEXT("Ray Tracing Global Illumination"));

void SetupLightParameters(
	const TSparseArray<FLightSceneInfoCompact>& Lights,
	const FViewInfo& View,
	FPathTracingLightData* LightParameters)
{
	LightParameters->Count = 0;

	// Prepend SkyLight to light buffer
	// WARNING: Until ray payload encodes Light data buffer, the execution depends on this ordering!
	uint32 SkyLightIndex = 0;
	LightParameters->Type[SkyLightIndex] = 0;
	LightParameters->Color[SkyLightIndex] = FVector(1.0);
	LightParameters->Count++;

	for (auto Light : Lights)
	{
		if (LightParameters->Count >= GLightCountMax) break;

		if (Light.LightSceneInfo->Proxy->HasStaticLighting() && Light.LightSceneInfo->IsPrecomputedLightingValid()) continue;
		if (!Light.LightSceneInfo->Proxy->AffectGlobalIllumination()) continue;

		FLightShaderParameters LightShaderParameters;
		Light.LightSceneInfo->Proxy->GetLightShaderParameters(LightShaderParameters);

		ELightComponentType LightComponentType = (ELightComponentType)Light.LightSceneInfo->Proxy->GetLightType();
		switch (LightComponentType)
		{
		case LightType_Directional:
		{
			LightParameters->Type[LightParameters->Count] = 2;
			LightParameters->Normal[LightParameters->Count] = LightShaderParameters.Direction;
			LightParameters->Color[LightParameters->Count] = LightShaderParameters.Color;
			LightParameters->Attenuation[LightParameters->Count] = 1.0 / LightShaderParameters.InvRadius;
			break;
		}
		case LightType_Rect:
		{
			LightParameters->Type[LightParameters->Count] = 3;
			LightParameters->Position[LightParameters->Count] = LightShaderParameters.Position;
			LightParameters->Normal[LightParameters->Count] = -LightShaderParameters.Direction;
			LightParameters->dPdu[LightParameters->Count] = FVector::CrossProduct(LightShaderParameters.Direction, LightShaderParameters.Tangent);
			LightParameters->dPdv[LightParameters->Count] = LightShaderParameters.Tangent;
			LightParameters->Color[LightParameters->Count] = LightShaderParameters.Color;
			LightParameters->Dimensions[LightParameters->Count] = FVector(2.0f * LightShaderParameters.SourceRadius, 2.0f * LightShaderParameters.SourceLength, 0.0f);
			LightParameters->Attenuation[LightParameters->Count] = 1.0 / LightShaderParameters.InvRadius;
			break;
		}
		case LightType_Point:
		default:
		{
			LightParameters->Type[LightParameters->Count] = 1;
			LightParameters->Position[LightParameters->Count] = LightShaderParameters.Position;
			// #dxr_todo: UE-72556 define these differences from Lit..
			LightParameters->Color[LightParameters->Count] = LightShaderParameters.Color / (4.0 * PI);
			float SourceRadius = 0.0; // LightShaderParameters.SourceRadius causes too much noise for little pay off at this time
			LightParameters->Dimensions[LightParameters->Count] = FVector(0.0, 0.0, SourceRadius);
			LightParameters->Attenuation[LightParameters->Count] = 1.0 / LightShaderParameters.InvRadius;
			break;
		}
		case LightType_Spot:
		{
			LightParameters->Type[LightParameters->Count] = 4;
			LightParameters->Position[LightParameters->Count] = LightShaderParameters.Position;
			LightParameters->Normal[LightParameters->Count] = -LightShaderParameters.Direction;
			// #dxr_todo: UE-72556 define these differences from Lit..
			LightParameters->Color[LightParameters->Count] = 4.0 * PI * LightShaderParameters.Color;
			float SourceRadius = 0.0; // LightShaderParameters.SourceRadius causes too much noise for little pay off at this time
			LightParameters->Dimensions[LightParameters->Count] = FVector(LightShaderParameters.SpotAngles, SourceRadius);
			LightParameters->Attenuation[LightParameters->Count] = 1.0 / LightShaderParameters.InvRadius;
			break;
		}
		};

		LightParameters->Count++;
	}
}

bool ShouldRenderRayTracingGlobalIllumination(const FViewInfo& View)
{
	if (!IsRayTracingEnabled())
	{
		return (false);
	}
	else if (GetForceRayTracingEffectsCVarValue() >= 0)
	{
		return GetForceRayTracingEffectsCVarValue() > 0;
	}
	else if (GRayTracingGlobalIllumination >= 0)
	{
		return (GRayTracingGlobalIllumination > 0);
	}
	else 
	{
		return View.FinalPostProcessSettings.RayTracingGI > 0;
	}
}

class FGlobalIlluminationRGS : public FGlobalShader
{
	DECLARE_GLOBAL_SHADER(FGlobalIlluminationRGS)
	SHADER_USE_ROOT_PARAMETER_STRUCT(FGlobalIlluminationRGS, FGlobalShader)

	class FUseAttenuationTermDim : SHADER_PERMUTATION_BOOL("USE_ATTENUATION_TERM");
	class FEnableTwoSidedGeometryDim : SHADER_PERMUTATION_BOOL("ENABLE_TWO_SIDED_GEOMETRY");

	using FPermutationDomain = TShaderPermutationDomain<FUseAttenuationTermDim, FEnableTwoSidedGeometryDim>;

	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return ShouldCompileRayTracingShadersForProject(Parameters.Platform);
	}

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		SHADER_PARAMETER(uint32, SamplesPerPixel)
		SHADER_PARAMETER(uint32, MaxBounces)
		SHADER_PARAMETER(uint32, UpscaleFactor)
		SHADER_PARAMETER(float, MaxRayDistanceForGI)
		SHADER_PARAMETER(float, MaxRayDistanceForAO)
		SHADER_PARAMETER(float, NextEventEstimationSamples)
		SHADER_PARAMETER(float, DiffuseThreshold)
		SHADER_PARAMETER(bool, EvalSkyLight)
		SHADER_PARAMETER(bool, UseRussianRoulette)
		SHADER_PARAMETER(float, MaxNormalBias)
		SHADER_PARAMETER(uint32, TileOffsetX)
		SHADER_PARAMETER(uint32, TileOffsetY)

		SHADER_PARAMETER_SRV(RaytracingAccelerationStructure, TLAS)
		SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D<float4>, RWGlobalIlluminationUAV)
		SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D<float>, RWRayDistanceUAV)
		SHADER_PARAMETER_STRUCT_REF(FViewUniformShaderParameters, ViewUniformBuffer)
		SHADER_PARAMETER_STRUCT_REF(FHaltonIteration, HaltonIteration)
		SHADER_PARAMETER_STRUCT_REF(FHaltonPrimes, HaltonPrimes)
		SHADER_PARAMETER_STRUCT_REF(FBlueNoise, BlueNoise)
		SHADER_PARAMETER_STRUCT_REF(FPathTracingLightData, LightParameters)
		SHADER_PARAMETER_STRUCT_REF(FSkyLightData, SkyLight)
		SHADER_PARAMETER_STRUCT_INCLUDE(FSceneTextureParameters, SceneTextures)
		SHADER_PARAMETER_RDG_TEXTURE(Texture2D, SSProfilesTexture)
		SHADER_PARAMETER_SAMPLER(SamplerState, TransmissionProfilesLinearSampler)
	END_SHADER_PARAMETER_STRUCT()
};

class FRayTracingGlobalIlluminationCompositePS : public FGlobalShader
{
	DECLARE_GLOBAL_SHADER(FRayTracingGlobalIlluminationCompositePS)
	SHADER_USE_PARAMETER_STRUCT(FRayTracingGlobalIlluminationCompositePS, FGlobalShader)

	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return ShouldCompileRayTracingShadersForProject(Parameters.Platform);
	}

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		RENDER_TARGET_BINDING_SLOTS()
		SHADER_PARAMETER_RDG_TEXTURE(Texture2D, GlobalIlluminationTexture)
		SHADER_PARAMETER_SAMPLER(SamplerState, GlobalIlluminationSampler)
		SHADER_PARAMETER_STRUCT_REF(FViewUniformShaderParameters, ViewUniformBuffer)
		SHADER_PARAMETER_STRUCT_INCLUDE(FSceneTextureParameters, SceneTextures)
	END_SHADER_PARAMETER_STRUCT()
};

class FRayTracingGlobalIlluminationSceneColorCompositePS : public FGlobalShader
{
	DECLARE_GLOBAL_SHADER(FRayTracingGlobalIlluminationSceneColorCompositePS)
	SHADER_USE_PARAMETER_STRUCT(FRayTracingGlobalIlluminationSceneColorCompositePS, FGlobalShader)

	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return ShouldCompileRayTracingShadersForProject(Parameters.Platform);
	}

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		RENDER_TARGET_BINDING_SLOTS()
		SHADER_PARAMETER_RDG_TEXTURE(Texture2D, GlobalIlluminationTexture)
		SHADER_PARAMETER_SAMPLER(SamplerState, GlobalIlluminationSampler)
		SHADER_PARAMETER_STRUCT_INCLUDE(FSceneTextureParameters, SceneTextures)
	END_SHADER_PARAMETER_STRUCT()
};

class FRayTracingGlobalIlluminationCHS : public FGlobalShader
{
	DECLARE_GLOBAL_SHADER(FRayTracingGlobalIlluminationCHS)
	SHADER_USE_ROOT_PARAMETER_STRUCT(FRayTracingGlobalIlluminationCHS, FGlobalShader)

	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return ShouldCompileRayTracingShadersForProject(Parameters.Platform);
	}

	using FParameters = FEmptyShaderParameters;
};

IMPLEMENT_GLOBAL_SHADER(FGlobalIlluminationRGS, "/Engine/Private/RayTracing/RayTracingGlobalIlluminationRGS.usf", "GlobalIlluminationRGS", SF_RayGen);
IMPLEMENT_GLOBAL_SHADER(FRayTracingGlobalIlluminationCHS, "/Engine/Private/RayTracing/RayTracingGlobalIlluminationRGS.usf", "RayTracingGlobalIlluminationCHS", SF_RayHitGroup);
IMPLEMENT_GLOBAL_SHADER(FRayTracingGlobalIlluminationCompositePS, "/Engine/Private/RayTracing/RayTracingGlobalIlluminationCompositePS.usf", "GlobalIlluminationCompositePS", SF_Pixel);
IMPLEMENT_GLOBAL_SHADER(FRayTracingGlobalIlluminationSceneColorCompositePS, "/Engine/Private/RayTracing/RayTracingGlobalIlluminationCompositePS.usf", "GlobalIlluminationSceneColorCompositePS", SF_Pixel);

void FDeferredShadingSceneRenderer::PrepareRayTracingGlobalIllumination(const FViewInfo& View, TArray<FRHIRayTracingShader*>& OutRayGenShaders)
{
	// Declare all RayGen shaders that require material closest hit shaders to be bound
	for (int UseAttenuationTerm = 0; UseAttenuationTerm < 2; ++UseAttenuationTerm)
	{
		for (int EnableTwoSidedGeometry = 0; EnableTwoSidedGeometry < 2; ++EnableTwoSidedGeometry)
		{
			FGlobalIlluminationRGS::FPermutationDomain PermutationVector;
			PermutationVector.Set<FGlobalIlluminationRGS::FUseAttenuationTermDim>(UseAttenuationTerm == 1);
			PermutationVector.Set<FGlobalIlluminationRGS::FEnableTwoSidedGeometryDim>(EnableTwoSidedGeometry == 1);
			TShaderMapRef<FGlobalIlluminationRGS> RayGenerationShader(View.ShaderMap, PermutationVector);
			OutRayGenShaders.Add(RayGenerationShader->GetRayTracingShader());
		}
	}

}

void FDeferredShadingSceneRenderer::RenderRayTracingGlobalIllumination(
	FRHICommandListImmediate& RHICmdList, 
	TRefCountPtr<IPooledRenderTarget>& GlobalIlluminationRT
)
{
	SCOPED_GPU_STAT(RHICmdList, RayTracingGlobalIllumination);

	bool bAnyViewWithRTGI = false;
	for (int32 ViewIndex = 0; ViewIndex < Views.Num(); ++ViewIndex)
	{
		FViewInfo& View = Views[ViewIndex];
		bAnyViewWithRTGI = bAnyViewWithRTGI || ShouldRenderRayTracingGlobalIllumination(View);
	}

	if (!bAnyViewWithRTGI)
	{
		return;
	}

	IScreenSpaceDenoiser::FAmbientOcclusionRayTracingConfig RayTracingConfig;
	RayTracingConfig.ResolutionFraction = 1.0;
	if (GRayTracingGlobalIlluminationDenoiser != 0)
	{
		RayTracingConfig.ResolutionFraction = FMath::Clamp(GRayTracingGlobalIlluminationScreenPercentage / 100.0, 0.25, 1.0);
	}

	int32 UpscaleFactor = int32(1.0 / RayTracingConfig.ResolutionFraction);

	FSceneRenderTargets& SceneContext = FSceneRenderTargets::Get(RHICmdList);
	{
		FPooledRenderTargetDesc Desc = SceneContext.GetSceneColor()->GetDesc();
		Desc.Format = PF_FloatRGBA;
		Desc.Flags &= ~(TexCreate_FastVRAM | TexCreate_Transient);
		GRenderTargetPool.FindFreeElement(RHICmdList, Desc, GlobalIlluminationRT, TEXT("RayTracingGlobalIllumination"));
	}

	FRDGBuilder GraphBuilder(RHICmdList);

	FRDGTextureRef GlobalIlluminationTexture;
	{
		FRDGTextureDesc Desc = SceneContext.GetSceneColor()->GetDesc();
		Desc.Extent /= UpscaleFactor;
		Desc.Format = PF_FloatRGBA;
		Desc.Flags &= ~(TexCreate_FastVRAM | TexCreate_Transient);
		GlobalIlluminationTexture = GraphBuilder.CreateTexture(Desc, TEXT("RayTracingGlobalIllumination"));
	}
	FRDGTextureUAV* GlobalIlluminationUAV = GraphBuilder.CreateUAV(FRDGTextureUAVDesc(GlobalIlluminationTexture));

	FRDGTextureRef RayDistanceTexture;
	{
		FRDGTextureDesc Desc = SceneContext.GetSceneColor()->GetDesc();
		Desc.Extent /= UpscaleFactor;
		Desc.Format = PF_G16R16;
		Desc.Flags &= ~(TexCreate_FastVRAM | TexCreate_Transient);
		RayDistanceTexture = GraphBuilder.CreateTexture(Desc, TEXT("RayTracingGlobalIlluminationRayDistance"));
	}
	FRDGTextureUAV* RayDistanceUAV = GraphBuilder.CreateUAV(FRDGTextureUAVDesc(RayDistanceTexture));

	TRefCountPtr<IPooledRenderTarget>& AmbientOcclusionRT = SceneContext.ScreenSpaceAO;

	for (int32 ViewIndex = 0; ViewIndex < Views.Num(); ++ViewIndex)
	{
		FViewInfo& View = Views[ViewIndex];
		if (ShouldRenderRayTracingGlobalIllumination(View))
		{
			RenderRayTracingGlobalIllumination(
				RHICmdList, 
				GraphBuilder, 
				View, 
				RayTracingConfig, 
				UpscaleFactor, 
				GlobalIlluminationRT, 
				AmbientOcclusionRT, 
				GlobalIlluminationUAV, 
				RayDistanceUAV, 
				GlobalIlluminationTexture, 
				RayDistanceTexture
			);
		}
	}

	GraphBuilder.Execute();
	SceneContext.bScreenSpaceAOIsValid = true;
	GVisualizeTexture.SetCheckPoint(RHICmdList, GlobalIlluminationRT);
}

void FDeferredShadingSceneRenderer::RenderRayTracingGlobalIllumination(
	FRHICommandListImmediate& RHICmdList,
	FRDGBuilder& GraphBuilder,
	FViewInfo& View,
	IScreenSpaceDenoiser::FAmbientOcclusionRayTracingConfig& RayTracingConfig,
	int32 UpscaleFactor,
	TRefCountPtr<IPooledRenderTarget>& GlobalIlluminationRT,
	TRefCountPtr<IPooledRenderTarget>& AmbientOcclusionRT,
	FRDGTextureUAV* GlobalIlluminationUAV,
	FRDGTextureUAV* RayDistanceUAV,
	const FRDGTextureRef GlobalIlluminationTexture,
	const FRDGTextureRef RayDistanceTexture
)
{	
	FSceneRenderTargets& SceneContext = FSceneRenderTargets::Get(RHICmdList);

	RDG_EVENT_SCOPE(GraphBuilder, "RTGI");

	int32 RayTracingGISamplesPerPixel = GRayTracingGlobalIlluminationSamplesPerPixel > -1 ? GRayTracingGlobalIlluminationSamplesPerPixel : View.FinalPostProcessSettings.RayTracingGISamplesPerPixel;
	RayTracingGISamplesPerPixel = FMath::Max(RayTracingGISamplesPerPixel, 0);
	RayTracingConfig.RayCountPerPixel = RayTracingGISamplesPerPixel;

	FSceneTextureParameters SceneTextures;
	SetupSceneTextureParameters(GraphBuilder, &SceneTextures);

	// Ray generation
	{
		uint32 IterationCount = FMath::Max(RayTracingGISamplesPerPixel, 1);
		uint32 SequenceCount = 1;
		uint32 DimensionCount = 24;
		FHaltonSequenceIteration HaltonSequenceIteration(Scene->HaltonSequence, IterationCount, SequenceCount, DimensionCount, View.ViewState ? (View.ViewState->FrameIndex % 1024) : 0);

		FHaltonIteration HaltonIteration;
		InitializeHaltonSequenceIteration(HaltonSequenceIteration, HaltonIteration);

		FHaltonPrimes HaltonPrimes;
		InitializeHaltonPrimes(Scene->HaltonPrimesResource, HaltonPrimes);

		FBlueNoise BlueNoise;
		InitializeBlueNoise(BlueNoise);

		FPathTracingLightData LightParameters;
		SetupLightParameters(Scene->Lights, View, &LightParameters);

		if (Scene->SkyLight && Scene->SkyLight->ShouldRebuildCdf())
		{
			BuildSkyLightCdfs(RHICmdList, Scene->SkyLight);
		}
		FSkyLightData SkyLightParameters;
		SetupSkyLightParameters(*Scene, &SkyLightParameters);

		FGlobalIlluminationRGS::FParameters* PassParameters = GraphBuilder.AllocParameters<FGlobalIlluminationRGS::FParameters>();
		PassParameters->SamplesPerPixel = RayTracingGISamplesPerPixel;
		PassParameters->MaxBounces = GRayTracingGlobalIlluminationMaxBounces > -1? GRayTracingGlobalIlluminationMaxBounces : View.FinalPostProcessSettings.RayTracingGIMaxBounces;
		PassParameters->MaxNormalBias = GetRaytracingMaxNormalBias();
		float MaxRayDistanceForGI = GRayTracingGlobalIlluminationMaxRayDistance;
		if (MaxRayDistanceForGI == -1.0)
		{
			MaxRayDistanceForGI = View.FinalPostProcessSettings.AmbientOcclusionRadius;
		}
		PassParameters->MaxRayDistanceForGI = MaxRayDistanceForGI;
		PassParameters->MaxRayDistanceForAO = View.FinalPostProcessSettings.AmbientOcclusionRadius;
		PassParameters->UpscaleFactor = UpscaleFactor;
		PassParameters->EvalSkyLight = GRayTracingGlobalIlluminationEvalSkyLight != 0;
		PassParameters->UseRussianRoulette = GRayTracingGlobalIlluminationUseRussianRoulette != 0;
		PassParameters->DiffuseThreshold = GRayTracingGlobalIlluminationDiffuseThreshold;
		PassParameters->NextEventEstimationSamples = GRayTracingGlobalIlluminationNextEventEstimationSamples;
		PassParameters->TLAS = View.RayTracingScene.RayTracingSceneRHI->GetShaderResourceView();
		PassParameters->ViewUniformBuffer = View.ViewUniformBuffer;
		PassParameters->HaltonIteration = CreateUniformBufferImmediate(HaltonIteration, EUniformBufferUsage::UniformBuffer_SingleDraw);
		PassParameters->HaltonPrimes = CreateUniformBufferImmediate(HaltonPrimes, EUniformBufferUsage::UniformBuffer_SingleDraw);
		PassParameters->BlueNoise = CreateUniformBufferImmediate(BlueNoise, EUniformBufferUsage::UniformBuffer_SingleDraw);
		PassParameters->LightParameters = CreateUniformBufferImmediate(LightParameters, EUniformBufferUsage::UniformBuffer_SingleDraw);
		PassParameters->SceneTextures = SceneTextures;
		PassParameters->SkyLight = CreateUniformBufferImmediate(SkyLightParameters, EUniformBufferUsage::UniformBuffer_SingleDraw);
		TRefCountPtr<IPooledRenderTarget> SubsurfaceProfileRT((IPooledRenderTarget*) GetSubsufaceProfileTexture_RT(RHICmdList));
		if (!SubsurfaceProfileRT)
		{
			SubsurfaceProfileRT = GSystemTextures.BlackDummy;
		}
		PassParameters->SSProfilesTexture = GraphBuilder.RegisterExternalTexture(SubsurfaceProfileRT);
		PassParameters->TransmissionProfilesLinearSampler = TStaticSamplerState<SF_Bilinear, AM_Clamp, AM_Clamp, AM_Clamp>::GetRHI();
		PassParameters->RWGlobalIlluminationUAV = GlobalIlluminationUAV;
		PassParameters->RWRayDistanceUAV = RayDistanceUAV;
		PassParameters->TileOffsetX = 0;
		PassParameters->TileOffsetY = 0;

		FGlobalIlluminationRGS::FPermutationDomain PermutationVector;
		PermutationVector.Set<FGlobalIlluminationRGS::FUseAttenuationTermDim>(true);
		PermutationVector.Set<FGlobalIlluminationRGS::FEnableTwoSidedGeometryDim>(CVarRayTracingGlobalIlluminationEnableTwoSidedGeometry.GetValueOnRenderThread() != 0);
		TShaderMapRef<FGlobalIlluminationRGS> RayGenerationShader(GetGlobalShaderMap(FeatureLevel), PermutationVector);
		ClearUnusedGraphResources(*RayGenerationShader, PassParameters);

		FIntPoint RayTracingResolution = FIntPoint::DivideAndRoundUp(View.ViewRect.Size(), UpscaleFactor);

		if (GRayTracingGlobalIlluminationTileSize <= 0)
		{
			GraphBuilder.AddPass(
				RDG_EVENT_NAME("GlobalIlluminationRayTracing %dx%d", RayTracingResolution.X, RayTracingResolution.Y),
				PassParameters,
				ERDGPassFlags::Compute,
				[PassParameters, this, &View, RayGenerationShader, RayTracingResolution](FRHICommandList& RHICmdList)
			{
				FRayTracingShaderBindingsWriter GlobalResources;
				SetShaderParameters(GlobalResources, *RayGenerationShader, *PassParameters);

				FRHIRayTracingScene* RayTracingSceneRHI = View.RayTracingScene.RayTracingSceneRHI;
				RHICmdList.RayTraceDispatch(View.RayTracingMaterialPipeline, RayGenerationShader->GetRayTracingShader(), RayTracingSceneRHI, GlobalResources, RayTracingResolution.X, RayTracingResolution.Y);
			});
		}
		else
		{
			int32 TileSize = FMath::Max(32, GRayTracingGlobalIlluminationTileSize);
			int32 NumTilesX = FMath::DivideAndRoundUp(RayTracingResolution.X, TileSize);
			int32 NumTilesY = FMath::DivideAndRoundUp(RayTracingResolution.Y, TileSize);
			for (int32 Y = 0; Y < NumTilesY; ++Y)
			{
				for (int32 X = 0; X < NumTilesX; ++X)
				{
					FGlobalIlluminationRGS::FParameters* TilePassParameters = PassParameters;

					if (X > 0 || Y > 0)
					{
						TilePassParameters = GraphBuilder.AllocParameters<FGlobalIlluminationRGS::FParameters>();
						*TilePassParameters = *PassParameters;

						TilePassParameters->TileOffsetX = X * TileSize;
						TilePassParameters->TileOffsetY = Y * TileSize;
					}

					int32 DispatchSizeX = FMath::Min<int32>(TileSize, RayTracingResolution.X - TilePassParameters->TileOffsetX);
					int32 DispatchSizeY = FMath::Min<int32>(TileSize, RayTracingResolution.Y - TilePassParameters->TileOffsetY);

					GraphBuilder.AddPass(
						RDG_EVENT_NAME("GlobalIlluminationRayTracing %dx%d (tile %dx%d)", DispatchSizeX, DispatchSizeY, X, Y),
						TilePassParameters,
						ERDGPassFlags::Compute,
						[TilePassParameters, this, &View, RayGenerationShader, DispatchSizeX, DispatchSizeY](FRHICommandList& RHICmdList)
					{
						FRHIRayTracingScene* RayTracingSceneRHI = View.RayTracingScene.RayTracingSceneRHI;

						FRayTracingShaderBindingsWriter GlobalResources;
						SetShaderParameters(GlobalResources, *RayGenerationShader, *TilePassParameters);
						RHICmdList.RayTraceDispatch(View.RayTracingMaterialPipeline, RayGenerationShader->GetRayTracingShader(), RayTracingSceneRHI, 
							GlobalResources, DispatchSizeX, DispatchSizeY);
						RHICmdList.SubmitCommandsHint();
					});
				}
			}
		}

	}

	// Denoising

	FRDGTextureRef ResultTexture; //#dxr_todo review

	if (GRayTracingGlobalIlluminationDenoiser != 0 && RayTracingGISamplesPerPixel > 0)
	{
		const IScreenSpaceDenoiser* DefaultDenoiser = IScreenSpaceDenoiser::GetDefaultDenoiser();
		const IScreenSpaceDenoiser* DenoiserToUse = GRayTracingGlobalIlluminationDenoiser == 1 ? DefaultDenoiser : GScreenSpaceDenoiser;

		IScreenSpaceDenoiser::FDiffuseIndirectInputs DenoiserInputs;
		DenoiserInputs.Color = GlobalIlluminationTexture;
		DenoiserInputs.RayHitDistance = RayDistanceTexture;

		{
			RDG_EVENT_SCOPE(GraphBuilder, "%s%s(DiffuseIndirect) %dx%d",
				DenoiserToUse != DefaultDenoiser ? TEXT("ThirdParty ") : TEXT(""),
				DenoiserToUse->GetDebugName(),
				View.ViewRect.Width(), View.ViewRect.Height());

			IScreenSpaceDenoiser::FDiffuseIndirectOutputs DenoiserOutputs = DenoiserToUse->DenoiseDiffuseIndirect(
				GraphBuilder,
				View,
				&View.PrevViewInfo,
				SceneTextures,
				DenoiserInputs,
				RayTracingConfig);

			ResultTexture = DenoiserOutputs.Color;
		}
	}
	else
	{
		ResultTexture = GlobalIlluminationTexture;
	}

	// Compositing
	{
		FRayTracingGlobalIlluminationCompositePS::FParameters *PassParameters = GraphBuilder.AllocParameters<FRayTracingGlobalIlluminationCompositePS::FParameters>();
		PassParameters->GlobalIlluminationTexture = ResultTexture;
		PassParameters->GlobalIlluminationSampler = TStaticSamplerState<SF_Point, AM_Clamp, AM_Clamp, AM_Clamp>::GetRHI();
		PassParameters->ViewUniformBuffer = View.ViewUniformBuffer;
		PassParameters->RenderTargets[0] = FRenderTargetBinding(GraphBuilder.RegisterExternalTexture(GlobalIlluminationRT), ERenderTargetLoadAction::ELoad, ERenderTargetStoreAction::EStore);
		PassParameters->RenderTargets[1] = FRenderTargetBinding(GraphBuilder.RegisterExternalTexture(AmbientOcclusionRT), ERenderTargetLoadAction::ELoad, ERenderTargetStoreAction::EStore);
		PassParameters->SceneTextures = SceneTextures;

		GraphBuilder.AddPass(
			RDG_EVENT_NAME("GlobalIlluminationComposite"),
			PassParameters,
			ERDGPassFlags::Raster,
			[this, &SceneContext, &View, &SceneTextures, PassParameters](FRHICommandListImmediate& RHICmdList)
			{
				TShaderMapRef<FPostProcessVS> VertexShader(View.ShaderMap);
				TShaderMapRef<FRayTracingGlobalIlluminationCompositePS> PixelShader(View.ShaderMap);
				FGraphicsPipelineStateInitializer GraphicsPSOInit;
				RHICmdList.ApplyCachedRenderTargets(GraphicsPSOInit);

				// Additive blending
				GraphicsPSOInit.BlendState = TStaticBlendState<CW_RGBA, BO_Add, BF_One, BF_Zero, BO_Add, BF_One, BF_Zero>::GetRHI();
				//GraphicsPSOInit.BlendState = TStaticBlendState<CW_RGBA, BO_Add, BF_One, BF_One, BO_Add, BF_One, BF_One>::GetRHI();
				GraphicsPSOInit.RasterizerState = TStaticRasterizerState<FM_Solid, CM_None>::GetRHI();
				GraphicsPSOInit.DepthStencilState = TStaticDepthStencilState<false, CF_Always>::GetRHI();

				GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI = GFilterVertexDeclaration.VertexDeclarationRHI;
				GraphicsPSOInit.BoundShaderState.VertexShaderRHI = GETSAFERHISHADER_VERTEX(*VertexShader);
				GraphicsPSOInit.BoundShaderState.PixelShaderRHI = GETSAFERHISHADER_PIXEL(*PixelShader);
				GraphicsPSOInit.PrimitiveType = PT_TriangleList;
				SetGraphicsPipelineState(RHICmdList, GraphicsPSOInit);

				SetShaderParameters(RHICmdList, *PixelShader, PixelShader->GetPixelShader(), *PassParameters);

				RHICmdList.SetViewport(View.ViewRect.Min.X, View.ViewRect.Min.Y, 0.0f, View.ViewRect.Max.X, View.ViewRect.Max.Y, 1.0f);

				DrawRectangle(
					RHICmdList,
					0, 0,
					View.ViewRect.Width(), View.ViewRect.Height(),
					View.ViewRect.Min.X, View.ViewRect.Min.Y,
					View.ViewRect.Width(), View.ViewRect.Height(),
					FIntPoint(View.ViewRect.Width(), View.ViewRect.Height()),
					SceneContext.GetBufferSizeXY(),
					*VertexShader
				);
			}
		);
	}
}

void FDeferredShadingSceneRenderer::CompositeGlobalIllumination(
	FRHICommandListImmediate& RHICmdList,
	const FViewInfo& View,
	TRefCountPtr<IPooledRenderTarget>& GlobalIlluminationRT
)
{
	FSceneRenderTargets& SceneContext = FSceneRenderTargets::Get(RHICmdList);

	FRDGBuilder GraphBuilder(RHICmdList);
	FSceneTextureParameters SceneTextures;
	SetupSceneTextureParameters(GraphBuilder, &SceneTextures);

	FRayTracingGlobalIlluminationSceneColorCompositePS::FParameters *PassParameters = GraphBuilder.AllocParameters<FRayTracingGlobalIlluminationSceneColorCompositePS::FParameters>();
	PassParameters->GlobalIlluminationTexture = GraphBuilder.RegisterExternalTexture(GlobalIlluminationRT);
	PassParameters->GlobalIlluminationSampler = TStaticSamplerState<SF_Point, AM_Clamp, AM_Clamp, AM_Clamp>::GetRHI();
	PassParameters->RenderTargets[0] = FRenderTargetBinding(GraphBuilder.RegisterExternalTexture(SceneContext.GetSceneColor()), ERenderTargetLoadAction::ELoad, ERenderTargetStoreAction::EStore);
	PassParameters->SceneTextures = SceneTextures;

	GraphBuilder.AddPass(
		RDG_EVENT_NAME("GlobalIlluminationComposite"),
		PassParameters,
		ERDGPassFlags::Raster,
		[this, &SceneContext, &View, PassParameters](FRHICommandListImmediate& RHICmdList)
		{
			TShaderMapRef<FPostProcessVS> VertexShader(View.ShaderMap);
			TShaderMapRef<FRayTracingGlobalIlluminationSceneColorCompositePS> PixelShader(View.ShaderMap);
			FGraphicsPipelineStateInitializer GraphicsPSOInit;
			RHICmdList.ApplyCachedRenderTargets(GraphicsPSOInit);

			// Additive blending
			GraphicsPSOInit.BlendState = TStaticBlendState<CW_RGBA, BO_Add, BF_One, BF_One, BO_Add, BF_One, BF_One>::GetRHI();
			//GraphicsPSOInit.BlendState = TStaticBlendState<CW_RGBA, BO_Add, BF_One, BF_One, BO_Add, BF_One, BF_One>::GetRHI();
			GraphicsPSOInit.RasterizerState = TStaticRasterizerState<FM_Solid, CM_None>::GetRHI();
			GraphicsPSOInit.DepthStencilState = TStaticDepthStencilState<false, CF_Always>::GetRHI();

			GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI = GFilterVertexDeclaration.VertexDeclarationRHI;
			GraphicsPSOInit.BoundShaderState.VertexShaderRHI = GETSAFERHISHADER_VERTEX(*VertexShader);
			GraphicsPSOInit.BoundShaderState.PixelShaderRHI = GETSAFERHISHADER_PIXEL(*PixelShader);
			GraphicsPSOInit.PrimitiveType = PT_TriangleList;
			SetGraphicsPipelineState(RHICmdList, GraphicsPSOInit);

			SetShaderParameters(RHICmdList, *PixelShader, PixelShader->GetPixelShader(), *PassParameters);

			RHICmdList.SetViewport(View.ViewRect.Min.X, View.ViewRect.Min.Y, 0.0f, View.ViewRect.Max.X, View.ViewRect.Max.Y, 1.0f);

			DrawRectangle(
				RHICmdList,
				0, 0,
				View.ViewRect.Width(), View.ViewRect.Height(),
				View.ViewRect.Min.X, View.ViewRect.Min.Y,
				View.ViewRect.Width(), View.ViewRect.Height(),
				FIntPoint(View.ViewRect.Width(), View.ViewRect.Height()),
				SceneContext.GetBufferSizeXY(),
				*VertexShader
			);
		}
	);
	GraphBuilder.Execute();
}

#endif // RHI_RAYTRACING
