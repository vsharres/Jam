// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "FactionManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJETOJAM_API UFactionManager : public UObject
{
	GENERATED_BODY()

private:

		UPROPERTY()
		TArray<class UFaction*> Factions;

public:

	UFactionManager(const FObjectInitializer& Initializer);

	UFUNCTION(BlueprintPure, Category = "Factions")
		TArray<UFaction*> GetFactions();

		
	
	
};
