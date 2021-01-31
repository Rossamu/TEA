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
	
	//It shortly ecxplains how the item looks like, how useful it is, and so on.
	//"\n" can be used for a line feed. (Becase line feed character is not available in UE4 editor)
	//�����ڂ␫�\�Ɋւ���Z������
	//"\n"�����邱�Ƃŉ��s�i�G�f�B�^�[��ŉ��s�����������Ȃ����߁j
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		FString Explanation;


	//The type "FIcon" will be defined in the future.
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		//FIcon Icon;


	//Functions
	UCPP_ItemBase() {
		PathToIconFilesDirectory = "/Game/Developers/KoichiYatsuduka/Items/Icons/";
	};
	~UCPP_ItemBase() {};
};
