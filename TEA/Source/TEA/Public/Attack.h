#pragma once

#include "Engine.h"
#include "CoreMinimal.h"
#include "Enum_ActionType.h"

#include "Attack.generated.h"

USTRUCT(BlueprintType, Blueprintable) //���܂��Ȃ�
struct FAttack
{
	GENERATED_USTRUCT_BODY()

public:

	//Variabls
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo")
		FString AttackName;

	//A specific combo which triggers this special attack.
	//���̓���U�����J��o�����߂̘A�g
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo")
		TArray<EActionType> TriggerCombo;

	//An animation montage which is played when this special attack is used.
	//���̓���U�����s��ꂽ�Ƃ��̃A�j���[�V���������^�[�W��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo")
	UAnimMontage* AnimMontage;



	//Don't call this.����͎g��Ȃ��B
	FAttack() {}


	//�g��������������BP�Ŏg���Ȃ�
	FAttack(TArray<EActionType> _TriggerCombo, UAnimMontage* _AnimMontage) {
		TriggerCombo = _TriggerCombo;
		AnimMontage = _AnimMontage;
	}

};