// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "NPCAgent.h"

ANPCAgent::ANPCAgent(const FObjectInitializer& Initializer)
	:Super(Initializer)
{
	bIsScripted = false;
}

void ANPCAgent::BeginPlay()
{
	Super::BeginPlay();

	AJAMGameState* gameState = Cast<AJAMGameState>(UGameplayStatics::GetGameState(this));
	check(gameState);

	gameState->OnAgentInit.AddDynamic(this, &ANPCAgent::InitializeAgent);

}

void ANPCAgent::InitializeAgent()
{
	Super::InitializeAgent();


}

void ANPCAgent::Interact()
{

}
