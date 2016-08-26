// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/LevelScriptActor.h"
#include "JAMLevelScript.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAgentInitSignature);
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Managers")
		UStatementDatabase* Database;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Managers")
		UFactionManager* FactionManager;

	UPROPERTY(BlueprintAssignable)
		FOnAgentInitSignature OnAgentInit;

	UPROPERTY(BlueprintAssignable)
		FOnAgentSpawedSignature OnAgentSpawned;

	UPROPERTY(BlueprintAssignable)
		FOnSaveGameSignature OnSaveGame;

	UFUNCTION(BlueprintCallable, Category = "Level")
		void InitializeGame();

	UFUNCTION(BlueprintCallable, Category = "Level")
		void SaveGameState();

	UFUNCTION(BlueprintCallable, Category = "Level")
		void LoadLevel();

	UFUNCTION(BlueprintCallable, Category = "Level")
		void InitializeManagers();


	
};
