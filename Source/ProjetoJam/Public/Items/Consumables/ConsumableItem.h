// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Items/Item.h"
#include "ConsumableItem.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PROJETOJAM_API UConsumableItem : public UItem
{
	GENERATED_BODY()

public:
	UConsumableItem(const FObjectInitializer& Initializer);

	UFUNCTION()
		virtual void ConsumeItem();
	
};
