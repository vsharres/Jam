// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "NPCAgent.h"

ANPCAgent::ANPCAgent(const FObjectInitializer& Initializer)
	:Super(Initializer)
{
	bIsScripted = false;
}

void ANPCAgent::InitializeAgent()
{
	AJAMLevelScript* Level = Cast<AJAMLevelScript>(GetLevel()->GetLevelScriptActor());

	if (Level)
	{
		Level->OnSaveGame.AddDynamic(this, &ANPCAgent::SaveState);
	}


	Super::InitializeAgent();
}

void ANPCAgent::Interact()
{

}

void ANPCAgent::SaveState()
{

}
