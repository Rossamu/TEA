#pragma once

#include "Engine.h"
#include "ItemBase.h"
#include "BattleItem.generated.h"

/**
 *
 */
USTRUCT(BlueprintType) //おまじない
struct FBattleItem : public FItemBase
{
	//おまじない2
	GENERATED_USTRUCT_BODY();

public:

	//Variabls
	


	//Functions
	FBattleItem();
	~FBattleItem();
};
