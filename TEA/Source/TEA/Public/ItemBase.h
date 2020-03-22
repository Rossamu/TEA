// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "ItemBase.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType) //‚¨‚Ü‚¶‚È‚¢
struct FItemBase
{
	//‚¨‚Ü‚¶‚È‚¢2
	GENERATED_USTRUCT_BODY();

public:

	//Variabls
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		FString Name;

	//The type "FIcon" will be defined in the future.
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		//FIcon Icon;


	//Functions
	FItemBase();
	~FItemBase();
};
