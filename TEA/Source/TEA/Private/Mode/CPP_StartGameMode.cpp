// Fill out your copyright notice in the Description page of Project Settings.

#include"CPP_DebugActionMode.h"

#include "CPP_StartGameMode.h"

#include "Engine/World.h"

#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

ACPP_StartGameMode::ACPP_StartGameMode()
	:Super()
{
	ModeManager = CreateDefaultSubobject<UCPP_GameModeManager>(TEXT("ModeManager"));
	ModeManager->NewMode(ACPP_DebugActionMode::StaticClass(), "DebugActionMode");

	FString CharacterPath = "/Game/Developers/mio/Contents/ParagonShinbi/Characters/Heroes/Shinbi/ShinbiPlayerCharacter.ShinbiPlayerCharacter_c";
	static ConstructorHelpers::FObjectFinder<UClass> CharacterBP(*CharacterPath);
	TSubclassOf<AActor> ThirdPersonCharacter = CharacterBP.Object;

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

	EnemyCharacterPath = "/Game/Developers/mio/Contents/MyEnemy/Enemy_Meca.Enemy_Meca_c";
	FVector EnemyPosition = FVector(100, 1424.302734, 91.790405);

	TSubclassOf<class AActor> EnemyCharacterBP = TSoftClassPtr<AActor>(FSoftObjectPath(*EnemyCharacterPath)).LoadSynchronous(); 
	if (EnemyCharacterBP)
	{
		AActor* EnemyCharacter = GetWorld()->SpawnActor<AActor>(EnemyCharacterBP, EnemyPosition, FRotator::ZeroRotator);
	}

/*	UClass* EnemyCharacterBP = LoadObject<UClass>(this, TEXT("Class'/Game/Developers/mio/Contents/MyEnemy/Enemy_Meca.Enemy_Meca_c'"));
	if (EnemyCharacterBP)
	{
		AActor* EnemyCharacter = GetWorld()->SpawnActor<AActor>(EnemyCharacterBP, EnemyPosition, FRotator::ZeroRotator);
		if (EnemyCharacter)
		{
			EnemyCharacter->SetActorLocation(EnemyPosition);
		}
	}
*/
}
