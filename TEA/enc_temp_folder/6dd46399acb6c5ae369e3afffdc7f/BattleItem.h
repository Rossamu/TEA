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
戦闘中に使う道具の抽象クラス
仮想関数としてUse関数をもち、これを呼び出すことでアイテムの効果を発生させるように実装する。
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
