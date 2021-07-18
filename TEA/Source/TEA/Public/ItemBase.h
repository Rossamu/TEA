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

	//定数

	UPROPERTY(BlueprintReadOnly, Category = "Item")
		FString PathToIconFilesDirectory;

	
	//変数
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Item")
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		FString IconImageName;
	
	//It shortly ecxplains how the item looks like, how useful it is, and so on.
	//"\n" can be used for a line feed. (Becase line feed character is not available in UE4 editor)
	//見た目や性能に関する短い説明
	//"\n"を入れることで改行（エディター上で改行文字を入れられないため）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		FString Explanation;


	//アイコン（小）用の画像.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintGetter=GetSmallIcon, Category = "Item")
	UTexture2D* SmallIcon;

	//アイコン（大）用の画像
	UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintGetter=GetLargeIcon,  Category = "Item")
	UTexture2D* LargeIcon;


	//Functions
	UCPP_ItemBase() {
		//PathToIconFilesDirectory = "/Game/Developers/KoichiYatsuduka/Items/Icons/";
	};
	~UCPP_ItemBase() {};

	//アイコンの受け渡し方が定まっていないため、関数による取得をする
	UFUNCTION(BlueprintPure, Category="Item")
		UTexture2D* GetSmallIcon() const;

	//アイコンの受け渡し方が定まっていないため、関数による取得をする
	UFUNCTION(BlueprintPure, Category="Item")
        UTexture2D* GetLargeIcon() const;
	
};
