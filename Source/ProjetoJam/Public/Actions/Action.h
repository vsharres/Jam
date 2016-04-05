// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Object.h"
#include "Action.generated.h"

struct FStatement;
class AAgent;

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class PROJETOJAM_API UAction : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	AAgent* Caller;

	UPROPERTY()
		TArray<FStatement> Postconditions;

	UPROPERTY()
		TArray<FStatement> Preconditions;

	UPROPERTY()
		UBehaviorTree* ActionBT;
	
	UAction();

	
	
};
