// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Agents/NPCs/NPCAgent.h"
#include "StarAgent.generated.h"


/**
 * 
 */
UCLASS()
class PROJETOJAM_API AStarAgent : public AAgent, public IInteract
{
	GENERATED_BODY()

	AStarAgent(const FObjectInitializer& Initializer);

	void InitializeAgent() override;

	void Interact() override;

	void SaveState() override;
	
};
