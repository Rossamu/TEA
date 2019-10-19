// Fill out your copyright notice in the Description page of Project Settings.

#include "Private/Mode/CPP_GameModeManager.h"
#include "Private/Mode/CPP_InitializeMode.h"

#include "CPP_DebugLevelScript.h"

void ACPP_DebugLevelScript::BeginPlay()
{
	UCPP_GameModeManager::SetInitGameMode(ACPP_InitializeMode::StaticClass(), TEXT(""));
}
