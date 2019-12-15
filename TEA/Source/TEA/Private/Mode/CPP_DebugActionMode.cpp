// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_DebugActionMode.h"

#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Engine/StreamableManager.h"
#include"Characters/Base/CPP_CharacterBase.h"
#include "Engine/World.h"

ACPP_DebugActionMode::ACPP_DebugActionMode()
	:Super()
{
	EnemyCharacterPath = "/Game/Developers/mio/Contents/MyEnemy/Enemy_Meca.Enemy_Meca_c";
	static ConstructorHelpers::FObjectFinder<UClass> EnemyCharacterBP(*EnemyCharacterPath);
	EnemyCharacter = EnemyCharacterBP.Object;

}

void ACPP_DebugActionMode::Initialize()
{

//	FString path = "/Game/test.test_C"; // /Content �ȉ��̃p�X�� /Game �ȉ��̃p�X�ɒu�������A�R���e���g�u���E�U�[�Ŗ��O�� test �Ȃ� test.test_C ���w�肷��B
//	TSubclassOf<class AActor> sc = TSoftClassPtr<AActor>(FSoftObjectPath(*EnemyCharacterPath)).LoadSynchronous(); // ��L�Őݒ肵���p�X�ɊY������N���X���擾
// if (sc != nullptr)
	{
//		AActor* a = GetWorld()->SpawnActor<AActor>(sc); // �X�|�[������
//		a->SetActorLocation(FVector(600, 1424.302734, 131.790405)); // �m�F���₷���悤�ɍ��W��ݒ�
	}
	// FGameLogicPlayerParameter = FDebugConfiguration::Instance().Player;

	// TODO : Create spawn class for player and configuration


}

void ACPP_DebugActionMode::Tick(float DeltaTime)
{

}

UCPP_CharacterBase* ACPP_DebugActionMode::GetEnemyCharacter()
{
	if (EnemyCharacter.IsPending())
	{
		const FSoftObjectPath& AssetRef = EnemyCharacter.ToStringReference();
		//EnemyCharacter = Cast<UCPP_CharacterBase>(Streamble)
	}


	return nullptr;
}
