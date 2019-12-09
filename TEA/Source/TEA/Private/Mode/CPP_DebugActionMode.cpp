// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_DebugActionMode.h"

#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include"Characters/Base/CPP_CharacterBase.h"

ACPP_DebugActionMode::ACPP_DebugActionMode()
	:Super()
{
	EnemyCharacterPath = "/Game/Developers/mio/Contents/MyEnemy/Enemy_Meca.Enemy_Meca_c";
	static ConstructorHelpers::FObjectFinder<UClass> EnemyCharacterBP(*EnemyCharacterPath);
	TSubclassOf<UClass> EnemyCharacter = EnemyCharacterBP.Object;

}

void ACPP_DebugActionMode::Initialize()
{


	// FGameLogicPlayerParameter = FDebugConfiguration::Instance().Player;

	// TODO : Create spawn class for player and configuration


}

void ACPP_DebugActionMode::Tick(float DeltaTime)
{

}
