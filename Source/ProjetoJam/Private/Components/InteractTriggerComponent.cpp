// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "Agents/Player/PlayerAgent.h"
#include "InteractTriggerComponent.h"


UInteractTriggerComponent::UInteractTriggerComponent()
{
	this->OnComponentBeginOverlap.AddDynamic(this, &UInteractTriggerComponent::OnTriggerBeginOverlap);
	bCanInteract = true;
}

void UInteractTriggerComponent::OnTriggerBeginOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	APlayerAgent* player = Cast<APlayerAgent>(OtherActor);

	if (bCanInteract && player->IsValidLowLevelFast())
	{
		player->SetCurInteractingActor(this->GetAttachmentRootActor());
	}
}

void UInteractTriggerComponent::OnTriggerEndOverlap(class UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayerAgent* player = Cast<APlayerAgent>(OtherActor);

}
