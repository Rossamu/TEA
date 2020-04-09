#pragma once

#include "Engine.h"
#include "CoreMinimal.h"
#include "ItemBase.h"
#include "Status.h"

#include "BattleItem.generated.h"

 
 
/*UENUM(BlueprintType)
enum class ETargetActor : uint8
{
	TA_Self			UMETA(DisplayName = "Self"),
	TA_Party		UMETA(DisplayName = "Party"),
	TA_Enemy		UMETA(DisplayName = "TargettedEnemy"),
	Num				UMETA(Hidden)
};*/

/*
�퓬���Ɏg������̒��ۃN���X
���z�֐��Ƃ���Use�֐��������A������Ăяo�����ƂŃA�C�e���̌��ʂ𔭐�������悤�Ɏ�������B
*/
UCLASS(BlueprintType, Blueprintable, Abstract) 
class TEA_API UCPP_BattleItemBase : public UCPP_ItemBase
{
	
	GENERATED_BODY()

public:

	//Variabls


	//Functions
	UFUNCTION(BlueprintCallable)
		void TestFunc(FStatus UserStatus) {};

	UCPP_BattleItemBase() {};
	~UCPP_BattleItemBase() {};


};
