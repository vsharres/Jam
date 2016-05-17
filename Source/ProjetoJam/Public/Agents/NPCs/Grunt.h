// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Agents/NPCs/NPCAgent.h"
#include "Grunt.generated.h"

/**
 * 
 */
UCLASS()
class PROJETOJAM_API AGrunt : public ANPCAgent
{
	GENERATED_BODY()
public:

	AGrunt(const FObjectInitializer& Initializer);
	
	void InitializeAgent() override;

	void Interact() override;
	
};
