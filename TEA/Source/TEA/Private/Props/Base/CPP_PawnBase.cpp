// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_PawnBase.h"

ACPP_PawnBase::ACPP_PawnBase()
	: Super()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.TickGroup = TG_PrePhysics;
}
