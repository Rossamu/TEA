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

	//It ecxplains how the item looks like, how useful it is, and so on.
	//å©ÇΩñ⁄Ç‚ê´î\Ç…ä÷Ç∑ÇÈê‡ñæ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		FString Explanation;


	UCPP_EquipmentBase();
	~UCPP_EquipmentBase();
};
