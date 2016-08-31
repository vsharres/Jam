// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "JAMGameInstance.generated.h"


/**
 * 
 */
UCLASS()
class PROJETOJAM_API UJAMGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Manager")
		UStatementDatabase* StatementDatabase;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Managers")
		UFactionManager* FactionManager;

	UJAMGameInstance();

		void Init() override;
	
	
};
