// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_ActorBase.h"

// Sets default values
ACPP_ActorBase::ACPP_ActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ACPP_ActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_ActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

