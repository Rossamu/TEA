// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/CPP_GameModeBase.h"
#include "CPP_DebugActionMode.generated.h"

/**
 * 
 */
UCLASS()
class ACPP_DebugActionMode : public ACPP_GameModeBase
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime)override;

protected:
	virtual void Initialize() override;
};
