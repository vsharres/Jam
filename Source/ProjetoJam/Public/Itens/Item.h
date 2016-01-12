// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Abstract)
class PROJETOJAM_API UItem : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
		FName Name;

	UItem(const FObjectInitializer& Initializer);
	
	
};
