// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Public/Agents/Agent.h"
#include "Jackie.generated.h"

/**
 * 
 */
UCLASS()
class PROJETOJAM_API AJackie : public AAgent
{
	GENERATED_BODY()
	
private:

	UPROPERTY()
	UCameraComponent* Camera;

	UPROPERTY()
	USpringArmComponent* CameraBoom;

public:

	AJackie(const FObjectInitializer& ObjectInitializer);
	
	
};
