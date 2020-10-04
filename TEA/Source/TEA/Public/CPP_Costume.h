#pragma once

#include "CoreMinimal.h"
#include "CPP_EquipmentBase.h"
#include "CPP_Costume.generated.h"

/*
将来的には衣装データへのポインタ（参照）を追加する
A pointer (reference) to data of costume will be added.
*/
UCLASS(BlueprintType, Blueprintable, Abstract)
class TEA_API UCPP_Costume : public UCPP_EquipmentBase
{
	GENERATED_BODY()
public:


	UCPP_Costume() {};
	~UCPP_Costume() {};
}; 
