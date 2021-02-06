// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/CPP_GameModeBase.h"
#include "CPP_InitializeMode.generated.h"

/**
 * 
 */
UCLASS()
class ACPP_InitializeMode : public ACPP_GameModeBase
{
	GENERATED_BODY()

public:

	virtual void Initialize()override;

private:

	void SetInitGameMode();
};
