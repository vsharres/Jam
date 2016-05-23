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
		UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Database", Keywords = "Get Database", WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"), Category = Database)
		static AStatementDatabase* GetStatementDatabase(UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Trace", Keywords = "Trace", WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"), Category = Trace)
		static bool Trace(UWorld* World, AActor* ActorToIgnore, const FVector& Start, const FVector& End, FHitResult& HitOut, ECollisionChannel CollisionChannel = ECC_Pawn, bool ReturnPhysMat = false);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TraceSphere", Keywords = "TraceSphere", WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"), Category = Trace)
		static bool TraceSphere(UWorld* World, AActor* ActorToIgnore, const FVector& Start, const FVector& End, const FRotator& Rot, TArray<FHitResult>& HitsOut, ECollisionChannel CollisionChannel = ECC_Pawn, bool ReturnPhysMat = false);


};
