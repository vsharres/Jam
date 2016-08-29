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

	UPROPERTY(EditDefaultsOnly, Category = Agent)
	TSubclassOf<class AAgent> AgentTypeToSpawn;

	UPROPERTY(VisibleAnywhere,Category = Billboard)
	UBillboardComponent* AgentBillboard;

	
public:	

	UFUNCTION()
	virtual void SpawnAgent();

	// Sets default values for this actor's properties
	AAgentSpawner(const FObjectInitializer& ObjectInitializer);

	void OnConstruction(const FTransform& Transform) override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	
};
