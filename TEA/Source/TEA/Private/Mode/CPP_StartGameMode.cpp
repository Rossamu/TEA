// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_StartGameMode.h"

#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

ACPP_StartGameMode::ACPP_StartGameMode()
	:Super()
{
	ModeManager = CreateDefaultSubobject<UCPP_GameModeManager>(TEXT("ModeManager"));

	static ConstructorHelpers::FObjectFinder< UClass > CharacterBP(TEXT("/Game/ThirdPersonBP/Blueprints/ThirdPersonCharacter.ThirdPersonCharacter_c"));
	TSubclassOf< class AActor > ThirdPersonCharacter = nullptr;
	ThirdPersonCharacter = CharacterBP.Object;
	if (ThirdPersonCharacter != nullptr)
	{
		DefaultPawnClass = ThirdPersonCharacter;
	}
}

void ACPP_StartGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACPP_StartGameMode::BeginPlay()
{
	Super::BeginPlay();

	
}
