#pragma once

#include "Engine.h"
#include "CoreMinimal.h"
#include "Status.generated.h"

USTRUCT(BlueprintType, Blueprintable) //おまじない
struct FStatus
{
	//おまじない2
	GENERATED_USTRUCT_BODY()

public:


	//Variabls
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float HP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float Max_HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float MP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float Max_MP;


	//Functions
	FStatus() {};
	~FStatus() {};

};
