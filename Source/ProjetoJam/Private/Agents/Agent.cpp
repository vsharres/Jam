// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoJam.h"
#include "PaperFlipbookComponent.h"
#include "Public/Agents/Agent.h"


AAgent::AAgent(const class FObjectInitializer& Initializer)
	: Super(Initializer)
{
	Stats = FAgentStats();
	Agent_Type = EAgentType::PLAYER;
	
}




