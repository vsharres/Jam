// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SphereComponent.h"
#include "InteractTriggerComponent.generated.h"

UENUM(BlueprintType)
enum class EInteractionType :uint8 {

	READ,
	TALK,
	PUSH,
	PRESS,
	OPEN,
	CLOSE,
	LOOT
};

/**
 * 
 */
UCLASS()
class PROJETOJAM_API UInteractTriggerComponent : public USphereComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = "InteractComponent")
		EInteractionType InteractionType;

	UInteractTriggerComponent(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category =  "InteractComponent")
	void OnTriggerBeginOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	UFUNCTION(BlueprintCallable, Category = "InteractComponent")
		void OnTriggerEndOverlap(class UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
