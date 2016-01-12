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

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* CameraBoom;


public:

	AJackie(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintPure, Category = "Camera")
	UCameraComponent* GetCamera();

	void MoveRight(float input) override;

	void MoveUp(float input) override;

	void InitializeAgent() override;

	void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
	
};
