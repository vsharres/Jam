// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "InteractiveSprite.h"
#include "InteractTriggerComponent.h"

AInteractiveSprite::AInteractiveSprite(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	InteractionTrigger = ObjectInitializer.CreateDefaultSubobject<UInteractTriggerComponent>(this, TEXT("Interaction Trigger"));
	FAttachmentTransformRules Rules(EAttachmentRule::KeepRelative, false);

	InteractionTrigger->AttachToComponent(RootComponent, Rules);
	InteractionTrigger->InteractionType = EInteractionType::READ;
	

}

void AInteractiveSprite::Interact()
{
	//TODO: SEND MESSAGE TO THE PLAYER TO INTERACT WITH THE OBJECT
}
