// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_EquipmentBase.h"
#include "CPP_Sword.generated.h"

/**
 * 
 */
UCLASS()
class TEA_API UCPP_Sword : public UCPP_EquipmentBase
{
	GENERATED_BODY()
public:
    int AttackPower;

    UCPP_Sword();
};
