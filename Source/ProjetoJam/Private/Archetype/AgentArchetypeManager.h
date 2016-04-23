// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Archetype/ArchetypeManager.h"
#include "AgentArchetypeManager.generated.h"

class AAgent;

/**
 * 
 */
UCLASS()
class UAgentArchetypeManager : public UArchetypeManager
{
	GENERATED_BODY()

private:

	UPROPERTY()
		AAgent* Agent;


	UAgentArchetypeManager();

	UFUNCTION()
		virtual void PopulateStatements();
	
	
	
	
};
