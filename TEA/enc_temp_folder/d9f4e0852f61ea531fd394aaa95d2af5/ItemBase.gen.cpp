// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TEA/Public/ItemBase.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeItemBase() {}
// Cross Module References
	TEA_API UScriptStruct* Z_Construct_UScriptStruct_FItemBase();
	UPackage* Z_Construct_UPackage__Script_TEA();
// End Cross Module References
class UScriptStruct* FItemBase::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern TEA_API uint32 Get_Z_Construct_UScriptStruct_FItemBase_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FItemBase, Z_Construct_UPackage__Script_TEA(), TEXT("ItemBase"), sizeof(FItemBase), Get_Z_Construct_UScriptStruct_FItemBase_Hash());
	}
	return Singleton;
}
template<> TEA_API UScriptStruct* StaticStruct<FItemBase>()
{
	return FItemBase::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FItemBase(FItemBase::StaticStruct, TEXT("/Script/TEA"), TEXT("ItemBase"), false, nullptr, nullptr);
static struct FScriptStruct_TEA_StaticRegisterNativesFItemBase
{
	FScriptStruct_TEA_StaticRegisterNativesFItemBase()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("ItemBase")),new UScriptStruct::TCppStructOps<FItemBase>);
	}
} ScriptStruct_TEA_StaticRegisterNativesFItemBase;
	struct Z_Construct_UScriptStruct_FItemBase_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Name;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FItemBase_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * \n *///???\xdc\x82??\xc8\x82?\n" },
		{ "ModuleRelativePath", "Public/ItemBase.h" },
		{ "ToolTip", "//???\xdc\x82??\xc8\x82?" },
	};
#endif
	void* Z_Construct_UScriptStruct_FItemBase_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FItemBase>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FItemBase_Statics::NewProp_Name_MetaData[] = {
		{ "Category", "Item" },
		{ "Comment", "//Variabls\n" },
		{ "ModuleRelativePath", "Public/ItemBase.h" },
		{ "ToolTip", "Variabls" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FItemBase_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FItemBase, Name), METADATA_PARAMS(Z_Construct_UScriptStruct_FItemBase_Statics::NewProp_Name_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FItemBase_Statics::NewProp_Name_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FItemBase_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FItemBase_Statics::NewProp_Name,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FItemBase_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_TEA,
		nullptr,
		&NewStructOps,
		"ItemBase",
		sizeof(FItemBase),
		alignof(FItemBase),
		Z_Construct_UScriptStruct_FItemBase_Statics::PropPointers,
		ARRAY_COUNT(Z_Construct_UScriptStruct_FItemBase_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FItemBase_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FItemBase_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FItemBase()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FItemBase_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_TEA();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("ItemBase"), sizeof(FItemBase), Get_Z_Construct_UScriptStruct_FItemBase_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FItemBase_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FItemBase_Hash() { return 2866862170U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
