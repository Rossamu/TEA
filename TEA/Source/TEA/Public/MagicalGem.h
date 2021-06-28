#pragma once
#include "CoreMinimal.h"
#include "ItemBase.h"
#include "../Private/Characters/CPP_PlayerCharacter.h"

#include "MagicalGem.generated.h"


//十字キー割り当て用
/*UENUM(BlueprintType)
enum class ED-Pad : unsigned int8
{
	MT_Up			UMETA(DisplayName = "D-Pad_Up"),
	MT_Right		UMETA(DisplayName = "D-Pad_Right"),
	MT_Down			UMETA(DisplayName = "D-Pad_Down"),
	MT_Left			UMETA(DisplayName = "D-Pad_Left"),
	Num				UMETA(Hidden)
};*/

class ACPP_PlayerCharacter;

UCLASS(BlueprintType, Blueprintable, Abstract)
class TEA_API UCPP_MagicalGem : public UCPP_ItemBase
{

	GENERATED_BODY()

public:

	//Variables

	//The number of remaind magics. 魔法残り回数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "MagicalGem")
		int32 RemainedMagic;

	//A reference for player class. Used to decide where the magic is spawned. プレイヤークラス参照。座標の取得とかに使う。
	UPROPERTY(EditAnywhere, Meta = (ExposeOnSpawn = "true"), BlueprintReadWrite)
		ACPP_PlayerCharacter* PlayerRef;

	//Used to display its shortened name in UIs. 短縮名。UI表示用に使うかも
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MagicalGem")
		FString AbbreviatedName;

	//アイコン（小）用画像
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MagicalGem")
		UTexture2D* SmallIcon;

	//詳細画面で見せる、大きい画像
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MagicalGem")
		UTexture2D* LargeIcon;
	
	//Functions

	//Execute the magic. Return true when success to do. 魔法実行。実行に成功すればtrue
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MagicalGem")
		bool ExecuteMagic() ;


	UCPP_MagicalGem() {}

	~UCPP_MagicalGem() {}

};
