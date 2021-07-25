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
			ShortcutItem.Add(Elem.Key, Elem.Value);
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
			NormaAttack();
		}
		else
		{
			Preinput = EActionType::NormalAttack;
			Pre_CancelAcceptance_sec = CancelAcceptanceLength_sec;
		}
	}

}

void ACPP_PlayerCharacter::NormaAttack()
{

}