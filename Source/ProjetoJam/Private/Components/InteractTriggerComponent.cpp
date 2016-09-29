// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "Agents/Player/PlayerAgent.h"
#include "InteractTriggerComponent.h"


UInteractTriggerComponent::UInteractTriggerComponent(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	OnComponentBeginOverlap.AddDynamic(this, &UInteractTriggerComponent::OnTriggerBeginOverlap);
	InteractionType = EInteractionType::TALK;
}

void UInteractTriggerComponent::OnTriggerBeginOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	APlayerAgent* player = Cast<APlayerAgent>(OtherActor);

	if (player && player->bCanInteract)
	{
		player->SetCurInteractingActor(this->GetAttachmentRootActor());
		player->ToggleInteractUI(InteractionType);
	}
}

void UInteractTriggerComponent::OnTriggerEndOverlap(class UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayerAgent* player = Cast<APlayerAgent>(OtherActor);

	if (player)
	{
		player->SetCurInteractingActor(NULL);
		player->ToggleInteractUI(InteractionType);
	}

}
