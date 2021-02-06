// Fill out your copyright notice in the Description page of Project Settings.
//テスト

#include "CPP_CharacterBase.h"

// Sets default values
ACPP_CharacterBase::ACPP_CharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPP_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

