// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Base/CPP_GameModeBase.h"

#include "UObject/NoExportTypes.h"
#include "CPP_GameModeManager.generated.h"

/**
 * 
 */
UCLASS()
class UCPP_GameModeManager : public UObject
{
	GENERATED_BODY()

public:

	UCPP_GameModeManager(const FObjectInitializer& ObjectInitializer);
	~UCPP_GameModeManager();


	ACPP_GameModeBase* NewMode(UClass* Class, const char *SubLevelName = nullptr);

	template<class T>
	T* NewMode(const char *SubLevelName = nullptr) { return Cast<T>(NewMode(T::StaticClass(), SubLevelName)); }

	FString SubLevelName;


	
private:
	
	void Initialize(TSubclassOf<ACPP_GameModeBase>ModeClass, const FString& LevelName = TEXT(""), const FString& = TEXT(""));
	void SetInitGameMode(TSubclassOf<ACPP_GameModeBase> ModeClass, const FString& LevelName);

	UPROPERTY()
		TArray<ACPP_GameModeBase*> Modes;

	FString InitLevelName;
};
