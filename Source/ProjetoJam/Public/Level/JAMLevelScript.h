// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/LevelScriptActor.h"
#include "JAMLevelScript.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAgentSpawedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSaveGameSignature);


/**
 * 
 */
UCLASS()
class PROJETOJAM_API AJAMLevelScript : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statements")
		TArray<FString> WorldStatements;

	UPROPERTY(BlueprintAssignable)
		FOnAgentSpawedSignature OnAgentSpawned;

	UPROPERTY(BlueprintAssignable)
		FOnSaveGameSignature OnSaveGame;

	AJAMLevelScript();

	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintCallable, Category = "Level")
		void InitializeWorldStatements();

	UFUNCTION(BlueprintCallable, Category = "Level")
		void LoadLevel();

	UFUNCTION(BlueprintCallable, Category = "Level")
		void SpawnAgents();

	UFUNCTION(BlueprintCallable, Category = "Level")
		void SaveGameState();
	
};
