// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Public/Agents/Agent.h"
#include "InteractTriggerComponent.h"
#include "PlayerAgent.generated.h"

/**
 * 
 */
UCLASS()
class PROJETOJAM_API APlayerAgent : public AAgent
{
	GENERATED_BODY()
	
private:

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = Inventory)
		UInventory* Inventory;

	UPROPERTY()
		TWeakObjectPtr<AActor> ActorToInteract;

	UPROPERTY()
		UTimelineComponent* CameraTraceTimeline;

	FOnTimelineEvent EventFunction{};


public:

	UPROPERTY(BlueprintReadWrite, Category = "Interact")
		bool bCanInteract;

	APlayerAgent(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintPure, Category = Interact)
		AActor* GetCurInteractingActor();

	UFUNCTION(BlueprintCallable, Category = Interact)
		void SetCurInteractingActor(AActor* Interactor);

	UFUNCTION(BlueprintPure, Category = Camera)
	UCameraComponent* GetCamera();

	UFUNCTION(BlueprintPure, Category = Inventory)
		UInventory* GetInventory();

	UFUNCTION(BlueprintCallable, Category = Interact)
		void InteractWith();
	
	UFUNCTION()
		void CameraTraceTimelineCallback();

	UFUNCTION(BlueprintCallable, Category = "Interact")
		void ToggleInteractUI(EInteractionType type);

	void BeginPlay() override;

	void MoveRight(float input) override;

	void MoveUp(float input) override;

	void UpdateFlipbook() override;

	virtual void Kill() override;

	void PostInitializeComponents() override;

	void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
};
