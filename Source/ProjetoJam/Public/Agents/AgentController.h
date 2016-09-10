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
	UPROPERTY()
	TArray<class UAction*> PossibleActions;

	UPROPERTY()
		UStatementDatabase* Database;

	UPROPERTY()
		float QueryCooldown;

	UPROPERTY()
		float QueryTimer;

public:

	UPROPERTY(BlueprintReadWrite, Category = "Action")
	class UAction* CurrentAction;

	AAgentController();

	UFUNCTION(BlueprintPure, Category = "Agent")
		FName GetAgentName();

	UFUNCTION(BlueprintCallable, Category = "Database")
		void QueryDatabase();

	UFUNCTION(BlueprintCallable, Category = "Action")
		void ChooseAction();

	UFUNCTION(BlueprintCallable, Category = "Action")
		void FinishBehavior();

	void BeginPlay() override;

	void PostInitializeComponents() override;

	FORCEINLINE static bool ConstPredicate(const FString& key1, const FString& key2)
	{
		return (key1 < key2);
	}
};
