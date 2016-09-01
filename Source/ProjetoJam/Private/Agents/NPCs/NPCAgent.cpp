// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "NPCAgent.h"

ANPCAgent::ANPCAgent(const FObjectInitializer& Initializer)
	:Super(Initializer)
{
	bIsScripted = false;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ANPCAgent::Interact()
{

}

void ANPCAgent::SaveState()
{

}
