// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "CPP_DebugLevelScript.generated.h"

/**
 * 
 */
UCLASS()
class ACPP_DebugLevelScript : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	void BeginPlay() override;
};
