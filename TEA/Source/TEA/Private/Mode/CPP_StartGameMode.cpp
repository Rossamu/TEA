// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_StartGameMode.h"
#include"CPP_DebugActionMode.h"


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

	EnemyCharacterPath = "/Game/Developers/mio/Contents/MyEnemy/Enemy_Meca.Enemy_Meca_c";
}

void ACPP_StartGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACPP_StartGameMode::BeginPlay()
{
	Super::BeginPlay();

	FVector EnemyPosition = FVector(100, 1424.302734, 91.790405);

/*	TSubclassOf<class AActor> sc = TSoftClassPtr<AActor>(FSoftObjectPath(*EnemyCharacterPath)).LoadSynchronous(); // 上記で設定したパスに該当するクラスを取得
	if (sc)
	{
		AActor* a = GetWorld()->SpawnActor<AActor>(sc); // スポーン処理
		a->SetActorLocation(EnemyPosition); // 確認しやすいように座標を設定
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
