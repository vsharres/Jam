// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Damage.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI, Blueprintable, meta = (CannotImplementInterfaceInBlueprint))
class UDamage : public UInterface
{
	GENERATED_UINTERFACE_BODY()
	
	
};

class IDamage
{
	GENERATED_IINTERFACE_BODY()

		UFUNCTION()
		virtual void OnDamaged(float Damage);
};
