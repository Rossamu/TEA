// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CPP_GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ACPP_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	void SetSubLevelName(const char* p)
	{
		SubLevelName = p;
	}

protected:

	virtual void Initialize() {};
	virtual void OnGoNext() {};

	FString SubLevelName;

};
