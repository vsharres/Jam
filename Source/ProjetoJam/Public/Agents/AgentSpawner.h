// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "AgentSpawner.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(AgentSpawnerLog, Log, All);

UCLASS()
class PROJETOJAM_API AAgentSpawner : public AActor
{
	GENERATED_BODY()


private:

	TSubclassOf<class AAgent> AgentTypeToSpawn;

	
public:	

	virtual void SpawnAgent();

	// Sets default values for this actor's properties
	AAgentSpawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
