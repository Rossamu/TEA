#pragma once

#include "Engine.h"
#include "CoreMinimal.h"
#include "Enum_ActionType.generated.h"

UENUM(BlueprintType)
enum class EActionType : uint8
{
	NormalAttack,
	SpecialAttack,
	MagicAttack,
	Dodge				UMETA(DisplayName = Roll),
	Step,
	None
};