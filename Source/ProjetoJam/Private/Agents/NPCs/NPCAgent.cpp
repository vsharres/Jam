// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "NPCAgent.h"

ANPCAgent::ANPCAgent(const FObjectInitializer& Initializer)
	:Super(Initializer)
{
	bIsScripted = false;
}

void ANPCAgent::OnConstruction(const FTransform& Transform)
{
	AJAMLevelScript* level = Cast<AJAMLevelScript>(GetLevel()->GetLevelScriptActor());
	check(level);
	level->OnAgentInit.AddDynamic(this, &ANPCAgent::InitializeAgent);

	Super::OnConstruction(Transform);
}

void ANPCAgent::InitializeAgent()
{
	Super::InitializeAgent();

}

void ANPCAgent::Interact()
{

}
