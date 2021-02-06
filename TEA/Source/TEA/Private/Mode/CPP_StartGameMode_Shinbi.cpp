// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_StartGameMode_Shinbi.h"
#include"CPP_DebugActionMode.h"


#include "Engine/World.h"

#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

ACPP_StartGameMode_Shinbi::ACPP_StartGameMode_Shinbi()
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

	EnemyCharacterPath = "/Game/Developers/mio/Contents/MyEnemy/Enemy_Meca.Enemy_Meca_c";
}

void ACPP_StartGameMode_Shinbi::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACPP_StartGameMode_Shinbi::BeginPlay()
{
	Super::BeginPlay();

	FVector EnemyPosition = FVector(100, 1424.302734, 91.790405);

/*	TSubclassOf<class AActor> sc = TSoftClassPtr<AActor>(FSoftObjectPath(*EnemyCharacterPath)).LoadSynchronous(); // ・ｽ・ｽL・ｽﾅ設定し・ｽ・ｽ・ｽp・ｽX・ｽﾉ該・ｽ・ｽ・ｽ・ｽ・ｽ・ｽN・ｽ・ｽ・ｽX・ｽ・ｽ・ｽ謫ｾ
	if (sc)
	{
		AActor* a = GetWorld()->SpawnActor<AActor>(sc); // ・ｽX・ｽ|・ｽ[・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ
		a->SetActorLocation(EnemyPosition); // ・ｽm・ｽF・ｽ・ｽ・ｽ竄ｷ・ｽ・ｽ・ｽ謔､・ｽﾉ搾ｿｽ・ｽW・ｽ・ｽﾝ抵ｿｽ
	}*/

	UClass* EnemyCharacterBP = LoadObject<UClass>(this, TEXT("Class'/Game/Developers/mio/Contents/MyEnemy/Enemy_Meca.Enemy_Meca_c'"));
	if (EnemyCharacterBP)
	{
		AActor* EnemyCharacter = GetWorld()->SpawnActor<AActor>(EnemyCharacterBP, EnemyPosition, FRotator::ZeroRotator);
		if (EnemyCharacter)
		{
			EnemyCharacter->SetActorLocation(EnemyPosition);
		}
	}
}
