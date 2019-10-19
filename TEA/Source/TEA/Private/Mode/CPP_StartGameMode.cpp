// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_StartGameMode.h"

ACPP_StartGameMode::ACPP_StartGameMode(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	ModeManager = CreateDefaultSubobject<UCPP_GameModeManager>(TEXT("ModeManager"));
}

void ACPP_StartGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACPP_StartGameMode::BeginPlay()
{
	Super::BeginPlay();
}
