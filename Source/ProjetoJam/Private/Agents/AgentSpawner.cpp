// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "Agent.h"
#include "AgentSpawner.h"
#include "LocationComponent.h"
#include "StatementsComponent.h"

DEFINE_LOG_CATEGORY(AgentSpawnerLog);

// Sets default values
AAgentSpawner::AAgentSpawner(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	Root = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Location"));
	FAttachmentTransformRules Rules(EAttachmentRule::KeepRelative, false);
	RootComponent = Root;

	LocationComponent = ObjectInitializer.CreateDefaultSubobject<ULocationComponent>(this, TEXT("Loc"));
	LocationComponent->AttachToComponent(RootComponent, Rules);

	AgentBillboard = ObjectInitializer.CreateDefaultSubobject<UBillboardComponent>(this, TEXT("Billboard"));
	AgentBillboard->AttachToComponent(RootComponent, Rules);

	StatementsComponent = ObjectInitializer.CreateDefaultSubobject<UStatementsComponent>(this, TEXT("Statements"));

	AgentTypeToSpawn = NULL;


}

void AAgentSpawner::PostInitializeComponents()
{
	AJAMLevelScript* level = Cast<AJAMLevelScript>(GetLevel()->GetLevelScriptActor());

	if (level && !level->OnAgentSpawned.Contains(this, TEXT("SpawnAgent")))
	{
		level->OnAgentSpawned.AddDynamic(this, &AAgentSpawner::SpawnAgent);
	}

	Super::PostInitializeComponents();
}

FName AAgentSpawner::GetSpawnerName()
{
	return SpawnerName;
}

TSubclassOf<AAgent> AAgentSpawner::GetAgentToSpawnType()
{
	return AgentTypeToSpawn;
}

void AAgentSpawner::SetAgentToSpawnType(TSubclassOf<AAgent> type)
{
	AgentTypeToSpawn = type;
}

void AAgentSpawner::SpawnAgent()
{
	if (AgentTypeToSpawn->IsValidLowLevelFast())
	{
		AAgent* AgentSpawned;

		AgentSpawned = GetWorld()->SpawnActor<AAgent>(AgentTypeToSpawn, this->GetActorLocation(), FRotator::ZeroRotator);

		if (!AgentSpawned)
		{
			UE_LOG(AgentSpawnerLog, Warning, TEXT("Cannot spawned the actor from the spawner %s"), *(this->GetName()));
			return;
		}

		AgentSpawned->SpawnDefaultController();
	}
	

}

