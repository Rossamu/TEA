// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Characters/Base/CPP_CharacterBase.h"
#include "CPP_PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ACPP_PlayerCharacter : public ACPP_CharacterBase
{
	GENERATED_BODY()

private:

	static const int32 MaxJumpCount = 2;

	// Called to bind functionality to input
	virtual void  SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	 // Called upon landing when falling, to perform actions based on the Hit result. 
	virtual void Landed(const FHitResult& Hit) override;

	void Jump();

	int32 JumpCount = 0;
};
