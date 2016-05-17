// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "Agent.h"
#include "AgentSpawner.h"

DEFINE_LOG_CATEGORY(AgentSpawnerLog);

// Sets default values
AAgentSpawner::AAgentSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AAgentSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAgentSpawner::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AAgentSpawner::SpawnAgent()
{
	AAgent* AgentSpawned;

	AgentSpawned = GetWorld()->SpawnActor<AAgent>(AgentTypeToSpawn, this->GetActorLocation(),FRotator::ZeroRotator);

	if (!AgentSpawned ? IsValidLowLevel() : NULL)
	{
		UE_LOG(AgentSpawnerLog, Warning, TEXT("Cannot spawned the actor from the spawner %s"), *(this->GetName()) );
	}

	AgentSpawned->SpawnDefaultController();
	AgentSpawned->InitializeAgent();

}

