// VRM4U Copyright (c) 2019 Haruyoshi Yamamoto. This software is released under the MIT License.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "Misc/EngineVersionComparison.h"
#include "VrmConvert.generated.h"

/**
 * 
 */

struct aiScene;
class UTexture2D;
class UMaterialInterface;
class USkeletalMesh;
class UVrmAssetListObject;
class UVrmLicenseObject;
class UPackage;

UENUM(BlueprintType)
enum EVRMImportMaterialType
{
	VRMIMT_Auto			UMETA(DisplayName = "Auto(MToon Unlit)"),
	VRMIMT_MToon		UMETA(DisplayName = "MToon Lit"),
	VRMIMT_MToonUnlit	UMETA(DisplayName = "MToon Unlit"),
	VRMIMT_Unlit		UMETA(DisplayName = "Unlit"),
	VRMIMT_glTF			UMETA(DisplayName = "PBR(glTF2)"),

	VRMIMT_MAX,
};


USTRUCT()
struct VRM4ULOADER_API FImportOptionData {
public:
	GENERATED_BODY()

	void init();
	bool bAPoseRetarget = true;

	bool bMobileBone = false;

	TEnumAsByte<enum EVRMImportMaterialType> MaterialType;

	float ModelScale = 1.0f;

	bool bCreateHumanoidRenamedMesh = false;

	bool bCreateIKBone = false;

	bool bSkipPhysics = false;

	bool bSkipMorphTarget = false;

	bool bEnableMorphTargetNormal = false;

	bool bNoTranslucent = false;

	bool bSingleUAssetFile = true;

	bool bMergeMaterial = true;

	bool bMergePrimitive = true;

	bool bOptimizeMaterial = true;

	bool bOptimizeVertex = true;

	bool bSimpleRoot = true;

	bool bSkipNoMeshBone = false;

	bool bDebugOneBone = false;

	UPROPERTY()
	class USkeleton* Skeleton;

};

class VRM4ULOADER_API VRMConverter {
public:
	static bool IsImportMode();
	static void SetImportMode(bool bImportMode);
	static FString NormalizeFileName(const char *str);
	static FString NormalizeFileName(const FString &str);

	static bool NormalizeBoneName(const aiScene *mScenePtr);

	static UTexture2D* CreateTexture(int32 InSizeX, int32 InSizeY, FString name, UPackage *package);
	static bool ConvertTextureAndMaterial(UVrmAssetListObject *vrmAssetList, const aiScene *mScenePtr);

	static bool ConvertModel(UVrmAssetListObject *vrmAssetList, const aiScene *mScenePtr);

	static bool ConvertMorphTarget(UVrmAssetListObject *vrmAssetList, const aiScene *mScenePtr);

	static UVrmLicenseObject *GetVRMMeta(const aiScene *mScenePtr);
	static bool ConvertVrmMeta(UVrmAssetListObject *vrmAssetList, const aiScene *mScenePtr);
	static bool ConvertHumanoid(UVrmAssetListObject *vrmAssetList, const aiScene *mScenePtr);
	static bool ConvertRig(UVrmAssetListObject *vrmAssetList, const aiScene *mScenePtr);

	static UPackage *CreatePackageFromImportMode(UPackage *p, const FString &name);

	class VRM4ULOADER_API Options {
	public:
		static Options & Get();

		const FImportOptionData *Window = nullptr;
		void SetVrmOption(const FImportOptionData *p) {
			Window = p;
		}

		class USkeleton *GetSkeleton();
		bool IsSimpleRootBone() const;

		bool IsSkipPhysics() const;

		bool IsSkipNoMeshBone() const;

		bool IsSkipMorphTarget() const;

		bool IsEnableMorphTargetNormal() const;

		bool IsCreateHumanoidRenamedMesh() const;

		bool IsCreateIKBone() const;

		bool IsDebugOneBone() const;

		bool IsMobileBone() const;

		bool IsNoTranslucent() const;

		bool IsSingleUAssetFile() const;

		bool IsMergeMaterial() const;

		bool IsMergePrimitive() const;

		bool IsOptimizeMaterial() const;

		bool IsOptimizeVertex() const;

		void ClearModelType();

		bool IsVRMModel() const;
		void SetVRMModel(bool bVRM);

		bool IsBVHModel() const;
		void SetBVHModel(bool bBVH);

		bool IsPMXModel() const;
		void SetPMXModel(bool bPMX);

		float GetModelScale() const;

		bool IsAPoseRetarget() const;

		EVRMImportMaterialType GetMaterialType() const;
		void SetMaterialType(EVRMImportMaterialType type);
	};
};


class VRM4ULOADER_API VrmConvert
{
public:
	VrmConvert();
	~VrmConvert();
};
