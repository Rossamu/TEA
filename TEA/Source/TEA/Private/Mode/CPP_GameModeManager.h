// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "CPP_GameModeManager.generated.h"

class ACPP_GameModeBase;
/**
 * 
 */
UCLASS()
class UCPP_GameModeManager : public UObject
{
	GENERATED_BODY()

public:

	UCPP_GameModeManager();
	~UCPP_GameModeManager();


	ACPP_GameModeBase* NewMode(UClass* Class, const char *SubLevelName = nullptr);

	template<class T>
	T* NewMode(const char *SubLevelName = nullptr) { return Cast<T>(NewMode(T::StaticClass(), SubLevelName)); }

	static void SetInitGameMode(TSubclassOf<ACPP_GameModeBase> ModeClass, const FString& LevelName);

	
private:
	
	void Initialize(TSubclassOf<ACPP_GameModeBase>ModeClass, const FString& LevelName = TEXT(""), const FString& = TEXT(""));

	UPROPERTY()
		TArray<ACPP_GameModeBase*> Modes;

	FString InitLevelName;
};
