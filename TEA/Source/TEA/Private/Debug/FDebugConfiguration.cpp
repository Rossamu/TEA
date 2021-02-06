// Fill out your copyright notice in the Description page of Project Settings.


#include "FDebugConfiguration.h"

FDebugConfiguration::FDebugConfiguration()
	:StartupModeName("")
{
}

FDebugConfiguration::~FDebugConfiguration()
{
}

// TODO : global variable
static FDebugConfiguration DebugConfigurationEntity;

FDebugConfiguration& FDebugConfiguration::Instance()
{
	return DebugConfigurationEntity;
}

