#pragma once

#include "Engine.h"
#include "CoreMinimal.h"
#include "Enum_ActionType.h"

#include "Attack.generated.h"

USTRUCT(BlueprintType, Blueprintable) //おまじない
struct FAttack
{
	GENERATED_USTRUCT_BODY()

public:

	//Variabls
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo")
		FString AttackName;

	//A specific combo which triggers this special attack.
	//この特殊攻撃を繰り出すための連携
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo")
		TArray<EActionType> TriggerCombo;

	//An animation montage which is played when this special attack is used.
	//この特殊攻撃が行われたときのアニメーションモンタージュ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo")
	UAnimMontage* AnimMontage;



	//Don't call this.これは使わない。
	FAttack() {}


	//使いたかったけどBPで使えない
	FAttack(TArray<EActionType> _TriggerCombo, UAnimMontage* _AnimMontage) {
		TriggerCombo = _TriggerCombo;
		AnimMontage = _AnimMontage;
	}

};