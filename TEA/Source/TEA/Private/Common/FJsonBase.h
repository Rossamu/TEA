// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#define TEA_ENABLE_JSON (PLATFORM_WINDOWS && !UE_BUILD_SHIPPING)
/**
 * 
 */
class FJsonBase
{
public:
	FJsonBase();
	~FJsonBase();
};
