// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "JamLibrary.generated.h"

/**
 *
 */
UCLASS()
class PROJETOJAM_API UJamLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", DisplayName = "Get Database", Keywords = "Get Database", WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"), Category = "Database")
		static UStatementDatabase* GetStatementDatabase(UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", DisplayName = "Get Faction Manager", Keywords = "Get Faction Manager", WorldContext = "WorldContextObject",  UnsafeDuringActorConstruction = "true"), Category = "Faction")
		static UFactionManager* GetFactionManager(UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", DisplayName = "Find Spawner", Keywords = "Find Spawner", WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"), Category = "Spawner")
		static AAgentSpawner* FindSpawner(UObject* WorldContextObject, FName spawnName);

	UFUNCTION(BlueprintCallable, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", DisplayName = "Instantiate Object", Keywords = "Instantiate Object"), Category = "Object")
		static UObject* InstantiateItem_Blueprint(UObject* WorldContextObject, TSubclassOf<UObject> Class);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Trace", Keywords = "Trace", UnsafeDuringActorConstruction = "true"), Category = "Trace")
		static bool Trace(UWorld* World, AActor* ActorToIgnore, const FVector& Start, const FVector& End, FHitResult& HitOut, ECollisionChannel CollisionChannel = ECC_Pawn, bool ReturnPhysMat = false);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TraceSphere", Keywords = "TraceSphere", UnsafeDuringActorConstruction = "true"), Category = "Trace")
		static bool TraceSphere(UWorld* World, AActor* ActorToIgnore, const FVector& Start, const FVector& End, const FRotator& Rot, float Radius, TArray<FHitResult>& HitsOut, ECollisionChannel CollisionChannel = ECC_Pawn, bool ReturnPhysMat = false);

	UFUNCTION(BlueprintCallable, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", DisplayName = "Generate DialogueTree", Keywords = "Instantiate Object"), Category = "Object")
		static UDialogueTree* GenerateDialogueTree(UObject* WorldContextObject, FStringAssetReference& DialogTreeAsset);

};
