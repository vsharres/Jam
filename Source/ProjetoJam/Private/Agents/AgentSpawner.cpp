// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "Agent.h"
#include "AgentSpawner.h"
#include "LocationComponent.h"

DEFINE_LOG_CATEGORY(AgentSpawnerLog);

// Sets default values
AAgentSpawner::AAgentSpawner(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	SceneComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, "Agent");
	RootComponent = SceneComponent;

	AgentBillboard = ObjectInitializer.CreateDefaultSubobject<UBillboardComponent>(this, "Billboard");
	FAttachmentTransformRules Rules(EAttachmentRule::KeepRelative, false);
	AgentBillboard->AttachToComponent(RootComponent, Rules);

	LocationComponent = ObjectInitializer.CreateDefaultSubobject<ULocationComponent>(this, "LocationTrigger");
	LocationComponent->AttachToComponent(RootComponent, Rules);

	AgentTypeToSpawn = NULL;

}

void AAgentSpawner::PostInitializeComponents()
{
	AJAMLevelScript* level = Cast<AJAMLevelScript>(GetLevel()->GetLevelScriptActor());

	if (level && !level->OnAgentSpawned.Contains(this, "SpawnAgent"))
	{
		level->OnAgentSpawned.AddDynamic(this, &AAgentSpawner::SpawnAgent);
	}

	Super::PostInitializeComponents();
}

// Called every frame
void AAgentSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	AAgent* AgentSpawned;

	AgentSpawned = GetWorld()->SpawnActor<AAgent>(AgentTypeToSpawn, this->GetActorLocation(), FRotator::ZeroRotator);

	if (!AgentSpawned)
	{
		UE_LOG(AgentSpawnerLog, Warning, TEXT("Cannot spawned the actor from the spawner %s"), *(this->GetName()));
	}

	AgentSpawned->SpawnDefaultController();

}

