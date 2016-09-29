// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "NPCAgent.h"
#include "InteractTriggerComponent.h"

ANPCAgent::ANPCAgent(const FObjectInitializer& Initializer)
	:Super(Initializer)
{
	bIsScripted = false;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	InteractionTrigger = Initializer.CreateDefaultSubobject<UInteractTriggerComponent>(this, TEXT("Interaction Trigger"));
	FAttachmentTransformRules Rules(EAttachmentRule::KeepRelative, false);
	InteractionTrigger->AttachToComponent(RootComponent, Rules);


}

void ANPCAgent::Interact()
{
	//TODO: Start a dialog interface
}

void ANPCAgent::SaveState()
{

}
