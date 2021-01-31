// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "CoreMinimal.h"

#include "Characters/Base/CPP_CharacterBase.h"
//#include "../../Public/Inventory.h"
#include "../../Public/Enum_ActionType.h"
#include "../../Public/CPP_Sword.h"
#include "../../Public/CPP_ArtificialLimbBase.h"
#include "../../Public/CPP_Costume.h"
//#include "../../Public/CPP_ArtificialLegs.h"
//#include "../../Public/CPP_ArtificialArm.h"
#include "../../Public/BattleItem.h"
#include "../../Public/CPP_EquipmentBase.h"
#include "../../Public/MagicalGem.h"
#include "CPP_PlayerCharacter.generated.h"

/*
�����ɂ��邢�����̍\���̂͊O���t�@�C���ɋL�q���ׂ���������Ȃ����A
�O���ɏ����ƃC���N���[�h�̃G���[�i����������j�ɂ��A�R���p�C�����ʂ�Ȃ����߁A�Վ��ł����ɋL�q����
*/


class UCPP_MagicalGem;


//�X�e�b�v����̂��߂ɗp����B�X�e�b�v�̕������ꎞ�L�^���邽�߂ɂ�������񋓌^
//Used for step-dodge. This enum type is used to memory stepping direction temporary. 
UENUM(BlueprintType)
enum class EStepDirection : uint8
{
	Front,
	Back,
	Left,
	Right,
	None
};

//���݂̑����i�����i�̃C���x���g���ł͂Ȃ��j�B�X�L����h���Z���������Q�Ƃ���B
//Current equipments. It does not mean an inventory of equipments. 
USTRUCT(BlueprintType, Blueprintable) //���܂��Ȃ�
struct FEquipments
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCPP_Sword* Sword;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCPP_ArtificialLimbBase* ArtificialLimb;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCPP_Costume* Costume;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCPP_ArtificialArm* ArtificialArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCPP_ArtificialLegs* ArtificialLegs;*/


};

//������g�p�\�Ȗ��@�͂��̒�����Q�Ƃ�����B
USTRUCT(BlueprintType) //���܂��Ȃ�
struct FInventory
{
	//���܂��Ȃ�2
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


/**
 * 
 */
UCLASS()
class ACPP_PlayerCharacter : public ACPP_CharacterBase
{
	GENERATED_BODY()

private:

	static const int32 MaxJumpCount = 2;

	

	// Called to bind functionality to input
	virtual void  SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	 // Called upon landing when falling, to perform actions based on the Hit result. 
	virtual void Landed(const FHitResult& Hit) override;

	void Jump();

	int32 JumpCount = 0;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FInventory Inventory;

};
