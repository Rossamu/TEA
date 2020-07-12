// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "CPP_ArtificialLimbBase.h"

#include "CPP_ArtificialLegs.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class TEA_API UCPP_ArtificialLegs : public UCPP_ArtificialLimbBase
{
	GENERATED_BODY()
public:
	UCPP_ArtificialLegs();
	~UCPP_ArtificialLegs();
};
