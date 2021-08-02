// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_PlayerCharacter.h"

#include "Components/InputComponent.h"
#include "GameFramework/PlayerInput.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"

static const float CancelAcceptanceLength_sec = 0.5f;

void ACPP_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// ショートカットのアイテム追加
	// BattleItemsの中から10種類のアイテムを初期装備
	for (const auto& Elem : Inventory.BattleItems)
	{
		if (ShortcutItem.Num() < MaxItemShortcutCount)
		{
			ShortcutItem.Add(Elem.Key);
		}
		else
		{
			break;
		}
	}

	// UseItemをBind
	InputComponent->BindAction("UseItem", IE_Pressed, this, &ACPP_PlayerCharacter::UseItem);
}

void ACPP_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	FInputActionKeyMapping jump("Jump", EKeys::Z, 0, 0, 0, 0);

	GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(jump);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACPP_PlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACPP_PlayerCharacter::StopJumping);
}

void ACPP_PlayerCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	JumpCount = 0;
}

void ACPP_PlayerCharacter::Jump()
{
	if (GetCharacterMovement()->IsFalling() && JumpCount < MaxJumpCount)
	{
		//To adjust the height of the second jump.
		const FVector JumpVelocity{ 0.0f, 0.0f, 800.0f };
		LaunchCharacter(JumpVelocity, false, false);

		JumpCount++;
	}
	else
	{
		Super::Jump();
		JumpCount++;
	}
}

void ACPP_PlayerCharacter::UseItem()
{

}

//void ACPP_PlayerCharacter::StopJumping()
//{
	
//}

void ACPP_PlayerCharacter::Attack()
{
	if (IsChainingCombo)
	{
		if (CanCancel)
		{
			// ノーマルアタック実行
			if (NormaAttack())
			{
				IsChainingCombo = true;
				CanCancel = false;
			}
		}
		else
		{
			Preinput = EActionType::NormalAttack;
			Pre_CancelAcceptance_sec = CancelAcceptanceLength_sec;
		}
	}
	else
	{
		// ノーマルアタック実行
		if (NormaAttack())
		{
			IsChainingCombo = true;
			CanCancel = false;
		}
	}
}

bool ACPP_PlayerCharacter::NormaAttack()
{
	for(const auto & Elem : Chain)
	{
		if ((Elem == EActionType::NormalAttack) || (Elem == EActionType::SpecialAttack))
		{
			Tmp_chain.Add(Elem);
		}
	}

	// ActiveAttackのAttackNameをチェック
	if (GetAvailableAttack().AttackName != "None")
	{
		// PlayAnimMontage実行
		PlayAnimMontage(Tmp_AttackElement.AnimMontage);
		
		// NormalAttackをチェーンに追加
		Chain.Add(EActionType::NormalAttack);
		
		return true;
	}
	else
	{
		return false;
	}
}

// 先行入力をしていて、尚且つキャンセル可能タイミングになった時に自動的に発火
void ACPP_PlayerCharacter::Precancel_attack()
{
	Pre_CancelAcceptance_sec = 0.0f;

	// ノーマルアタック実行
	if (NormaAttack())
	{
		IsChainingCombo = true;
		CanCancel = false;
	}
}

FAttack ACPP_PlayerCharacter::GetAvailableAttack()
{
	for (const auto& Elem : Chain)
	{
		if ((Elem == EActionType::NormalAttack) || (Elem == EActionType::SpecialAttack))
		{
			Tmp_chain.Add(Elem);
		}
	}

	for (const auto& Elem : AvailableAttackList)
	{
		Tmp_AttackElement = Elem;

		// AvailableAttackListのTriggerComboとTmp_chainを比較
		if (CompareAnyActionType(Tmp_chain, Elem.TriggerCombo))
		{
			return Tmp_AttackElement;
		}
	}

	if (IsValid(Equipments.ArtificialLimb))
	{
		ArtLimb = Equipments.ArtificialLimb;

		// AvailableAttackListのTriggerComboとArtLimb SpecificSpecialAttack.TriggerComboを比較
		if (CompareAnyActionType(Tmp_chain, ArtLimb->SpecificSpecialAttack.TriggerCombo))
		{
			return ArtLimb->SpecificSpecialAttack;
		}
	}

	// Make Attack(新しいAttackを生成してreturn)
	FAttack NewAttack;
	return NewAttack;
}

bool ACPP_PlayerCharacter::CompareAnyActionType(TArray<EActionType> a, TArray<EActionType> b)
{
	if (a.Num() == b.Num())
	{
		for (int32 index = 0; index < a.Num(); index++)
		{
			if (a[index] != b[index])
			{
				return false;
			}
		}

		return true;
	}
	else
	{
		return false;
	}
}

void ACPP_PlayerCharacter::Smash()
{
	if (IsChainingCombo)
	{
		if (CanCancel)
		{
			// スペシャルアタック実行
			if (SpecialAttack())
			{
				IsChainingCombo = true;
				CanCancel = false;
			}
		}
		else
		{
			Preinput = EActionType::SpecialAttack;
			Pre_CancelAcceptance_sec = CancelAcceptanceLength_sec;
		}
	}
	else
	{
		// スペシャルアタック実行
		if (SpecialAttack())
		{
			IsChainingCombo = true;
			CanCancel = false;
		}
	}
}

void ACPP_PlayerCharacter::Precancel_Smash()
{
	Pre_CancelAcceptance_sec = 0.0f;

	// スペシャルアタック実行
	if (SpecialAttack())
	{
		IsChainingCombo = true;
		CanCancel = false;
	}
}

bool ACPP_PlayerCharacter::SpecialAttack()
{
	for (const auto& Elem : Chain)
	{
		if ((Elem == EActionType::NormalAttack) || (Elem == EActionType::SpecialAttack))
		{
			Tmp_chain.Add(Elem);
		}
	}

	// ActiveAttackのAttackNameをチェック
	if (GetAvailableAttack().AttackName != "None")
	{
		// PlayAnimMontage実行
		PlayAnimMontage(Tmp_AttackElement.AnimMontage);

		// SpecialAttackをチェーンに追加
		Chain.Add(EActionType::SpecialAttack);

		return true;
	}
	else
	{
		return false;
	}
}


void ACPP_PlayerCharacter::ResetCombo()
{
	Chain;

	IsChainingCombo = false;
	CanCancel = false;
	IsRolling = false;
	IsStepping = false;
}