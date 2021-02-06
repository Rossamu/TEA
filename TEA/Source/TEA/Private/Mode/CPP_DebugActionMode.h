// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/CPP_GameModeBase.h"
#include "CPP_DebugActionMode.generated.h"

class UCPP_CharacterBase;

/**
 * 
 */
UCLASS()
class ACPP_DebugActionMode : public ACPP_GameModeBase
{
	GENERATED_BODY()

public:

	ACPP_DebugActionMode();

	virtual void Tick(float DeltaTime)override;

	UCPP_CharacterBase* GetEnemyCharacter();

protected:

	virtual void Initialize() override;

private:
	FString EnemyCharacterPath;

	TSoftObjectPtr<UCPP_CharacterBase> EnemyCharacter;
};
