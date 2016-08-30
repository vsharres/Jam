// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "AgentController.generated.h"

/**
 * 
 */
UCLASS()
class PROJETOJAM_API AAgentController : public AAIController
{
	GENERATED_BODY()

private:
	TMap<FString, class UAction*> PossibleActions;

	UPROPERTY()
		UStatementDatabase* Database;

public:

	UPROPERTY(BlueprintReadWrite, Category = "Action")
	class UAction* CurrentAction;

	AAgentController();

	UFUNCTION(BlueprintPure, Category = "Agent")
		FName GetAgentName();

	void QueryDatabase();

	UFUNCTION(BlueprintCallable , Category = "Action")
		void StopBehavior();

	void BeginPlay() override;

	FORCEINLINE static bool ConstPredicate(const FString& key1, const FString& key2)
	{
		return (key1 < key2);
	}
};
