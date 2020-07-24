// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Characters/Base/CPP_CharacterBase.h"
#include "../../Public/Inventory.h"
#include "../../Public/Enum_ActionType.h"
#include "../../Public/CPP_Sword.h"
#include "../../Public/CPP_ArtificialLegs.h"
#include "../../Public/CPP_ArtificialArm.h"

#include "CPP_PlayerCharacter.generated.h"


UENUM(BlueprintType)
enum class EStepDirection : uint8
{
	Front,
	Back,
	Left,
	Right,
	None
};

USTRUCT(BlueprintType, Blueprintable) //‚¨‚Ü‚¶‚È‚¢
struct FEquipments
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCPP_Sword* Sword;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCPP_ArtificialArm* ArtificialArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCPP_ArtificialLegs* ArtificialLegs;


};

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

protected:

	FInventory Inventory;

public:


};
