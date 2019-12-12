// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	virtual void  SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void Landed(const FHitResult& Hit) override;

	void Jump();
	//void StopJumping();

	int32 JumpCount = 0;

};
