// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_DebugActionMode.h"

#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

ACPP_DebugActionMode::ACPP_DebugActionMode()
	:Super()
{

}

void ACPP_DebugActionMode::Initialize()
{
	// FGameLogicPlayerParameter = FDebugConfiguration::Instance().Player;

	// TODO : Create spawn class for player and configuration

	FString Path = "/Game/ThirdPersonBP/Blueprints/ThirdPersonCharacter.ThirdPersonCharacter_c";
	ConstructorHelpers::FObjectFinder<UClass> CharacterBP(*Path);
	TSubclassOf<AActor> ThirdPersonCharacter = CharacterBP.Object;

	if (ThirdPersonCharacter != nullptr)
	{
		Enemy = ThirdPersonCharacter;
	}

}

void ACPP_DebugActionMode::Tick(float DeltaTime)
{

}
