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
	Super::InitializeAgent();
}

void AStarAgent::Interact()
{
	Super::Interact();
}

