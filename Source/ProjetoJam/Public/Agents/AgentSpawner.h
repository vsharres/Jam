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

	UPROPERTY(VisibleAnywhere, Category = "Root")
		USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, Category = "Agent")
	TSubclassOf<class AAgent> AgentTypeToSpawn;

	UPROPERTY(VisibleAnywhere,Category = "Billboard")
	UBillboardComponent* AgentBillboard;

	UPROPERTY(EditAnywhere, Category = "Location")
		class ULocationComponent* LocationComponent;

	UPROPERTY(EditAnywhere, Category = "Spawner")
		FName SpawnerName;

	
public:	

	UFUNCTION(BlueprintPure, Category = "Spawner")
		FName GetSpawnerName();

	UFUNCTION(BlueprintPure, Category = "Spawner")
		TSubclassOf<AAgent> GetAgentToSpawnType();

	UFUNCTION(BlueprintCallable, Category = "Spawner")
		void SetAgentToSpawnType(TSubclassOf<AAgent> type);

	UFUNCTION()
	virtual void SpawnAgent();

	// Sets default values for this actor's properties
	AAgentSpawner(const FObjectInitializer& ObjectInitializer);

	void PostInitializeComponents() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	
};
