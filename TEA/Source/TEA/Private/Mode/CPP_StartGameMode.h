// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/CPP_GameModeBase.h"

#include "CPP_StartGameMode.generated.h"


/**
 * 
 */
UCLASS()
class ACPP_StartGameMode : public ACPP_GameModeBase
{
	GENERATED_BODY()

public:

	ACPP_StartGameMode();
	~ACPP_StartGameMode() {}

	virtual void Tick(float DeltaTime)override;
	virtual void BeginPlay() override;

};
