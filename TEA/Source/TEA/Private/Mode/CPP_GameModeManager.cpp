// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_GameModeManager.h"
#include "Kismet/GameplayStatics.h"
//#include "../Common/FJsonBase.h"
#include "Base/CPP_GameModeBase.h"



UCPP_GameModeManager::UCPP_GameModeManager(const FObjectInitializer& ObjectInitializer)
//	:Super(ObjectInitializer)
	:Modes()
{
	if (GetWorld())
	{
		s_pInst = this;
	}
}

UCPP_GameModeManager::~UCPP_GameModeManager()
{
}

ACPP_GameModeBase* UCPP_GameModeManager::NewMode(UClass * Class, const char * SubLevelName)
{
	ACPP_GameModeBase* NewMode = NewObject<ACPP_GameModeBase>(this, Class);

	if (NewMode)
	{
		// TODO : Add Inport Data of Json

		if (SubLevelName)
		{
			if (!strcmp(SubLevelName, "Initialize"))
			{
				//			NewMode->
			}
		}
		
		NewMode->ModeManager = this;
		NewMode->Initialize();
		Modes.Add(NewMode);
	}
	return NewMode;
}

void UCPP_GameModeManager::Initialize(TSubclassOf<ACPP_GameModeBase> ModeClass, const FString & LevelName, const FString &)
{
	// Ç±ÇÍÇ¢ÇÈÅH
	InitLevelName = LevelName;

	// debug
	// extern void InitializeDebugSelectMode();

//#if TEA_ENABLE_JSON
	// Import Json Method
//#endif
	ACPP_GameModeBase* Mode = NewMode(ModeClass, TCHAR_TO_ANSI(*LevelName));
}


 TWeakObjectPtr<UCPP_GameModeManager> UCPP_GameModeManager::s_pInst;
 void UCPP_GameModeManager::SetInitGameMode(TSubclassOf<ACPP_GameModeBase> ModeClass, const FString& LevelName)
 {
	 // TODO : Load Stream Level 
	  //FLatentActionInfo Info;
	  //UGameplayStatics::LoadStreamLevel(GetWorld(), FName(*LevelName), false, true, Info);

	 UCPP_GameModeManager* inst = s_pInst.Get();

	 if (inst)
	 {
		 inst->Initialize(ModeClass, LevelName, LevelName);
	 }
 }
