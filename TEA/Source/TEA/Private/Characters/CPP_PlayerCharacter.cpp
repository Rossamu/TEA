// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_PlayerCharacter.h"

#include "Components/InputComponent.h"
#include "GameFramework/PlayerInput.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"

void ACPP_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

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



//void ACPP_PlayerCharacter::StopJumping()
//{
	
//}
