// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "StarAgent.h"

AStarAgent::AStarAgent(const FObjectInitializer& Initializer)
	:Super(Initializer)
{
	Agent_Type = EAgentType::SPECIAL;
}

void AStarAgent::PostInitializeComponents()
{
	AJAMLevelScript* Level = Cast<AJAMLevelScript>(GetLevel()->GetLevelScriptActor());

	if (Level && !Level->OnSaveGame.Contains(this,"SaveState"))
	{
		Level->OnSaveGame.AddDynamic(this, &AStarAgent::SaveState);
	}

	Super::PostInitializeComponents();
}

void AStarAgent::Interact()
{

}

void AStarAgent::SaveState()
{

}

