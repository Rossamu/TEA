// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "ItemBase.h"

#include "CPP_EquipmentBase.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, Abstract)
class TEA_API UCPP_EquipmentBase : public UCPP_ItemBase
{
	GENERATED_BODY()
public:
	UCPP_EquipmentBase();
	~UCPP_EquipmentBase();
};
