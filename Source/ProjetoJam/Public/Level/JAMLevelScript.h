// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/LevelScriptActor.h"
#include "JAMLevelScript.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAgentInitSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDatabaseInitSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSaveGameSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAgentSpawedSignature);

/**
 * 
 */
UCLASS()
class PROJETOJAM_API AJAMLevelScript : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintAssignable)
		FOnAgentInitSignature OnAgentInit;

	UPROPERTY(BlueprintAssignable)
		FOnDatabaseInitSignature OnDatabaseInit;

	UPROPERTY(BlueprintAssignable)
		FOnAgentSpawedSignature OnAgentSpawned;

	UPROPERTY(BlueprintAssignable)
		FOnSaveGameSignature OnSaveGame;


	UFUNCTION(BlueprintCallable, Category = Level)
		void InitializeGame();

	UFUNCTION(BlueprintCallable, Category = Level)
		void SaveGameState();


	
};
