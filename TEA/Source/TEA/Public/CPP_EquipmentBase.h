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

	//It shortly ecxplains how the item looks like, how useful it is, and so on.
	//見た目や性能に関する短い説明
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		//FString Explanation;

	//It ecxplains how the item looks like, how useful it is, and so on in details.
	//見た目や性能に関する詳しい説明
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		FString Explanation_Full;

	UCPP_EquipmentBase();
	~UCPP_EquipmentBase();
};
