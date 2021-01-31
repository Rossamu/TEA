/*#pragma once

#include "Structs.h"
#include "Engine.h"
#include "CoreMinimal.h"

#include "BattleItem.h"
#include "CPP_EquipmentBase.h"
#include "MagicalGem.h"

#include "Inventory.generated.h"

class UCPP_MagicalGem;

USTRUCT(BlueprintType) //‚¨‚Ü‚¶‚È‚¢
struct FInventory
{
	//‚¨‚Ü‚¶‚È‚¢2
	GENERATED_USTRUCT_BODY();

public:

	//Variabls


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		TMap<UCPP_BattleItemBase*, int32> BattleItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		TArray<UCPP_MagicalGem*> MagicalGems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		TArray<UCPP_EquipmentBase*> Equipments;



	
	//Functions
	FInventory() {};
	~FInventory() {};
};
*/