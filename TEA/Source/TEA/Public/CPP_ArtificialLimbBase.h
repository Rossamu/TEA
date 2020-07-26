// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "CPP_EquipmentBase.h"
#include "Attack.h"

#include "CPP_ArtificialLimbBase.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, Abstract)
class TEA_API UCPP_ArtificialLimbBase : public UCPP_EquipmentBase
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAttack SpecificSpecialAttack;

	UCPP_ArtificialLimbBase();
	~UCPP_ArtificialLimbBase();
};
