// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "StarAgent.h"

AStarAgent::AStarAgent(const FObjectInitializer& Initializer)
	:Super(Initializer)
{
	Agent_Type = EAgentType::SPECIAL;
}

void AStarAgent::InitializeAgent()
{

	AJAMLevelScript* Level = Cast<AJAMLevelScript>(GetLevel()->GetLevelScriptActor());

	if (Level)
	{
		Level->OnSaveGame.AddDynamic(this, &AStarAgent::SaveState);
	}

	Super::InitializeAgent();
}

void AStarAgent::Interact()
{

}

void AStarAgent::SaveState()
{

}

