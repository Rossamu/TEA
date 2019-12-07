// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_DebugLevelScript.h"
#include "Private/Mode/CPP_GameModeManager.h"
#include "Private/Mode/CPP_DebugActionMode.h"


void ACPP_DebugLevelScript::BeginPlay()
{
	UCPP_GameModeManager::SetInitGameMode(ACPP_DebugActionMode::StaticClass(), TEXT(""));

}
