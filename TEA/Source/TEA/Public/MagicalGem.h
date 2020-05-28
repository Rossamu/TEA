#pragma once
#include "CoreMinimal.h"
#include "ItemBase.h"
#include "../Private/Characters/CPP_PlayerCharacter.h"

#include "MagicalGem.generated.h"

//�\���L�[���蓖�ėp
/*UENUM(BlueprintType)
enum class ED-Pad : unsigned int8
{
	MT_Up			UMETA(DisplayName = "D-Pad_Up"),
	MT_Right		UMETA(DisplayName = "D-Pad_Right"),
	MT_Down			UMETA(DisplayName = "D-Pad_Down"),
	MT_Left			UMETA(DisplayName = "D-Pad_Left"),
	Num				UMETA(Hidden)
};*/

UCLASS(BlueprintType, Blueprintable, Abstract)
class TEA_API UCPP_MagicalGem : public UCPP_ItemBase
{

	GENERATED_BODY()

public:

	//Variabls

	//The number of remaind magics. ���@�c���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "MagicalGem")
		int RemainedMagic;

	//A reference for player class. Used to decide where the magic is spawned. �v���C���[�N���X�Q�ƁB���W�̎擾�Ƃ��Ɏg���B
	UPROPERTY(EditAnywhere, Meta = (ExposeOnSpawn = true), BlueprintReadWrite)
		ACPP_PlayerCharacter* PlayerRef;

	//Used to display its shortened name in UIs. �Z�k���BUI�\���p�Ɏg������
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MagicalGem")
		FString AbbreviatedName;
	
	//Functions

	//Execute the magic. Return true when success to do. ���@���s�B���s�ɐ��������true
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MagicalGem")
		bool ExecuteMagic();


	UCPP_MagicalGem() {}

	~UCPP_MagicalGem() {}

};
