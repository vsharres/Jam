// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Sprite/FadableSprite.h"
#include "InteractiveSprite.generated.h"

/**
 * 
 */
UCLASS()
class PROJETOJAM_API AInteractiveSprite : public AFadableSprite, public IInteract
{
	GENERATED_BODY()
	
private:

	UPROPERTY(VisibleAnywhere, Category = "Trigger")
	class UInteractTriggerComponent* InteractionTrigger;

public:

	AInteractiveSprite(const FObjectInitializer& ObjectInitializer);

	virtual void Interact();
	
	
};
