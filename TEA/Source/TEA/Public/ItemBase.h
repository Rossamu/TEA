// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "CoreMinimal.h"
#include "ItemBase.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, Abstract) 
class TEA_API UCPP_ItemBase : public UObject
{
	GENERATED_BODY()

public:

	//const

	UPROPERTY(BlueprintReadOnly, Category = "Item")
		FString PathToIconFilesDirectory;

	//Variabls
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		FString IconImageName;
	

	//The type "FIcon" will be defined in the future.
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		//FIcon Icon;


	//Functions
	UCPP_ItemBase() {
		PathToIconFilesDirectory = "/Game/Developers/KoichiYatsuduka/Items/Icons/";
	};
	~UCPP_ItemBase() {};
};
