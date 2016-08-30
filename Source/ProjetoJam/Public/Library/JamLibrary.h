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
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Database", Keywords = "Get Database", WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"), Category = "Database")
		static UStatementDatabase* GetStatementDatabase(UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Faction Manager", Keywords = "Get Faction Manager", WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"), Category = "Faction")
		static UFactionManager* GetFactionManager(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", DisplayName = "Instantiate Object", Keywords = "Instantiate Object"), Category = "Object")
		static UObject* InstantiateItem_Blueprint(UObject* WorldContextObject, TSubclassOf<UObject> Class);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Trace", Keywords = "Trace", WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"), Category = "Trace")
		static bool Trace(UWorld* World, AActor* ActorToIgnore, const FVector& Start, const FVector& End, FHitResult& HitOut, ECollisionChannel CollisionChannel = ECC_Pawn, bool ReturnPhysMat = false);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TraceSphere", Keywords = "TraceSphere", WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"), Category = "Trace")
		static bool TraceSphere(UWorld* World, AActor* ActorToIgnore, const FVector& Start, const FVector& End, const FRotator& Rot, float Radius, TArray<FHitResult>& HitsOut, ECollisionChannel CollisionChannel = ECC_Pawn, bool ReturnPhysMat = false);


};
