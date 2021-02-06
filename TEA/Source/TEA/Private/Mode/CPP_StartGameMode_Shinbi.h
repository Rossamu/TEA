// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/CPP_GameModeBase.h"

#include "CPP_StartGameMode_Shinbi.generated.h"


/**
 * 
 */
UCLASS()
class ACPP_StartGameMode_Shinbi : public ACPP_GameModeBase
{
	GENERATED_BODY()

public:

	ACPP_StartGameMode_Shinbi();
	~ACPP_StartGameMode_Shinbi() {}

	virtual void Tick(float DeltaTime)override;
	virtual void BeginPlay() override;

	FString EnemyCharacterPath;

};
