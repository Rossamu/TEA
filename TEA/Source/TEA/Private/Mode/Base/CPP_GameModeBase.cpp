// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_GameModeBase.h"

ACPP_GameModeBase::ACPP_GameModeBase(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
	,ModeManager(nullptr)
{
}

ACPP_GameModeBase::~ACPP_GameModeBase()
{
}

void ACPP_GameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void ACPP_GameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
