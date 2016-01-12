// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interact.generated.h"

/**
 *
 */
UINTERFACE(MinimalAPI, Blueprintable, meta = (CannotImplementInterfaceInBlueprint))
class UInteract : public UInterface
{
	GENERATED_UINTERFACE_BODY()


};

class IInteract
{
	GENERATED_IINTERFACE_BODY()

		UFUNCTION()
		virtual void Interact();


};
