// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Archetype/ArchetypeManager.h"
#include "FactionArchetypeManager.generated.h"

class UFaction;

/**
 * 
 */
UCLASS()
class PROJETOJAM_API UFactionArchetypeManager : public UArchetypeManager
{
	GENERATED_BODY()

		UPROPERTY()
		UFaction* Faction;

	UFactionArchetypeManager();

	UFUNCTION()
		virtual void PopulateStatements();
	
	
};
