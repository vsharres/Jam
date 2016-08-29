// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Faction.h"
#include "FactionManager.generated.h"

#define FACTIONS_DATABASE_PATH (FString)(FPaths::GameContentDir() + "Databases/Factions/Faction.xml")

/**
 * 
 */
UCLASS()
class PROJETOJAM_API UFactionManager : public UObject
{
	GENERATED_BODY()

private:

		UPROPERTY()
		TArray<UFaction*> Factions;

public:

	UFactionManager(const FObjectInitializer& Initializer);

	UFUNCTION(BlueprintPure, Category = "Faction")
		TArray<UFaction*> GetFactions();

	UFUNCTION(BlueprintPure, Category = "Faction")
		UFaction* GetFaction(EFactionType type);

	UFUNCTION(BlueprintCallable, Category = "Faction")
		void InitializeFactions();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Parse Factions Files", Keywords = "Parse Factions Files"), Category = "Faction Manager")
		void ParseFactionsFile();
		
	
};
