// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "CoreMinimal.h"
#include "ItemBase.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable) //‚¨‚Ü‚¶‚È‚¢
class TEA_API UCPP_ItemBase : public UObject
{
	//‚¨‚Ü‚¶‚È‚¢2
	GENERATED_BODY()

public:


	//Variabls
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		FString Name;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		//FString Bnmv;
	//The type "FIcon" will be defined in the future.
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		//FIcon Icon;


	//Functions
	UCPP_ItemBase() {};
	~UCPP_ItemBase() {};
};
