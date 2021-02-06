// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Private/Mode/CPP_GameModeManager.h"
#include "CPP_GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ACPP_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	friend class UCPP_GameModeManager;
	
public:

	ACPP_GameModeBase();
	~ACPP_GameModeBase();

	void SetSubLevelName(const char* p)
	{
		SubLevelName = p;
	}

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:

	virtual void Initialize() {};
	virtual void OnGoNext() {};

	FString SubLevelName;

	UPROPERTY()
		UCPP_GameModeManager* ModeManager;

};
