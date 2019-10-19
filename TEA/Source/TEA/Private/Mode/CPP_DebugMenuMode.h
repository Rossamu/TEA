// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/CPP_GameModeBase.h"
#include "CPP_DebugMenuMode.generated.h"

/**
 * 
 */
UCLASS()
class ACPP_DebugMenuMode : public ACPP_GameModeBase
{
	GENERATED_BODY()
	
public:

	virtual void Tick( float DeltaSeconds ) override;
	virtual void ResetLevel() override;
	virtual void Initialize() override;

private:
	

};
