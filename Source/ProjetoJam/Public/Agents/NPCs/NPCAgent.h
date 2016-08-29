// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Agents/Agent.h"
#include "Interact.h"
#include "NPCAgent.generated.h"

/**
 * 
 */
UCLASS()
class PROJETOJAM_API ANPCAgent : public AAgent, public IInteract
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = NPC)
		bool bIsScripted;

	ANPCAgent(const FObjectInitializer& Initializer);

	void InitializeAgent() override;

	void Interact() override;

	void SaveState() override;
	
	
};
