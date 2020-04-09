// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TEA/Public/BattleItem.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBattleItem() {}
// Cross Module References
	TEA_API UClass* Z_Construct_UClass_UCPP_BattleItemBase_NoRegister();
	TEA_API UClass* Z_Construct_UClass_UCPP_BattleItemBase();
	TEA_API UClass* Z_Construct_UClass_UCPP_ItemBase();
	UPackage* Z_Construct_UPackage__Script_TEA();
	TEA_API UFunction* Z_Construct_UFunction_UCPP_BattleItemBase_Use();
	TEA_API UScriptStruct* Z_Construct_UScriptStruct_FStatus();
// End Cross Module References
	static FName NAME_UCPP_BattleItemBase_Use = FName(TEXT("Use"));
	FStatus UCPP_BattleItemBase::Use(FStatus UserStatus)
	{
		CPP_BattleItemBase_eventUse_Parms Parms;
		Parms.UserStatus=UserStatus;
		ProcessEvent(FindFunctionChecked(NAME_UCPP_BattleItemBase_Use),&Parms);
		return Parms.ReturnValue;
	}
	void UCPP_BattleItemBase::StaticRegisterNativesUCPP_BattleItemBase()
	{
		UClass* Class = UCPP_BattleItemBase::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "Use", &UCPP_BattleItemBase::execUse },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UCPP_BattleItemBase_Use_Statics
	{
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_UserStatus;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UCPP_BattleItemBase_Use_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CPP_BattleItemBase_eventUse_Parms, ReturnValue), Z_Construct_UScriptStruct_FStatus, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UCPP_BattleItemBase_Use_Statics::NewProp_UserStatus = { "UserStatus", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CPP_BattleItemBase_eventUse_Parms, UserStatus), Z_Construct_UScriptStruct_FStatus, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCPP_BattleItemBase_Use_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCPP_BattleItemBase_Use_Statics::NewProp_ReturnValue,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCPP_BattleItemBase_Use_Statics::NewProp_UserStatus,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCPP_BattleItemBase_Use_Statics::Function_MetaDataParams[] = {
		{ "Comment", "//Functions\n" },
		{ "ModuleRelativePath", "Public/BattleItem.h" },
		{ "ToolTip", "Functions" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCPP_BattleItemBase_Use_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCPP_BattleItemBase, nullptr, "Use", nullptr, nullptr, sizeof(CPP_BattleItemBase_eventUse_Parms), Z_Construct_UFunction_UCPP_BattleItemBase_Use_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UFunction_UCPP_BattleItemBase_Use_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x0C020C00, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCPP_BattleItemBase_Use_Statics::Function_MetaDataParams, ARRAY_COUNT(Z_Construct_UFunction_UCPP_BattleItemBase_Use_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCPP_BattleItemBase_Use()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCPP_BattleItemBase_Use_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UCPP_BattleItemBase_NoRegister()
	{
		return UCPP_BattleItemBase::StaticClass();
	}
	struct Z_Construct_UClass_UCPP_BattleItemBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UCPP_BattleItemBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UCPP_ItemBase,
		(UObject* (*)())Z_Construct_UPackage__Script_TEA,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UCPP_BattleItemBase_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UCPP_BattleItemBase_Use, "Use" }, // 3710999498
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCPP_BattleItemBase_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/*\n?\xed\x93\xac???\xc9\x8eg???????\xcc\x92??\xdb\x83N???X\n???z?\xd6\x90??\xc6\x82???Use?\xd6\x90????????A???????\xc4\x82\xd1\x8fo?????\xc6\x82\xc5\x83""A?C?e???\xcc\x8c??\xca\x82\xf0\x94\xad\x90????????\xe6\x82\xa4?\xc9\x8e????????B\n*/" },
		{ "IncludePath", "BattleItem.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/BattleItem.h" },
		{ "ToolTip", "?\xed\x93\xac???\xc9\x8eg???????\xcc\x92??\xdb\x83N???X\n???z?\xd6\x90??\xc6\x82???Use?\xd6\x90????????A???????\xc4\x82\xd1\x8fo?????\xc6\x82\xc5\x83""A?C?e???\xcc\x8c??\xca\x82\xf0\x94\xad\x90????????\xe6\x82\xa4?\xc9\x8e????????B" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UCPP_BattleItemBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCPP_BattleItemBase>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UCPP_BattleItemBase_Statics::ClassParams = {
		&UCPP_BattleItemBase::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x001000A1u,
		METADATA_PARAMS(Z_Construct_UClass_UCPP_BattleItemBase_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_UCPP_BattleItemBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UCPP_BattleItemBase()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UCPP_BattleItemBase_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UCPP_BattleItemBase, 3708636613);
	template<> TEA_API UClass* StaticClass<UCPP_BattleItemBase>()
	{
		return UCPP_BattleItemBase::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UCPP_BattleItemBase(Z_Construct_UClass_UCPP_BattleItemBase, &UCPP_BattleItemBase::StaticClass, TEXT("/Script/TEA"), TEXT("UCPP_BattleItemBase"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UCPP_BattleItemBase);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
