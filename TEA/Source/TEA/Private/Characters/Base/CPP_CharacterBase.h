// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPP_CharacterBase.generated.h"

UENUM(BlueprintType)
enum class EActionType : uint8
{
	NormalAttack		,
	SpecialAttack		,
	MagicAttack			,
	Dodge				,
	None
};

UCLASS()
class ACPP_CharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACPP_CharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
