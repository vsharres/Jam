// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "JAMGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJETOJAM_API AJAMGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadWrite, Category = "Manager")
		class UFactionManager* FactionManager;

	UPROPERTY(BlueprintReadWrite, Category = "Manager")
		UStatementDatabase* StatementDatabase;

	AJAMGameMode(const FObjectInitializer& Initializer);

	UFUNCTION(BlueprintCallable, Category = "GameMode")
		void InitializeManagers();

	
	
};
