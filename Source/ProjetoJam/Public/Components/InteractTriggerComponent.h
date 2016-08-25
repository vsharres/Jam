// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SphereComponent.h"
#include "InteractTriggerComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJETOJAM_API UInteractTriggerComponent : public USphereComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InteractComponent)
		bool bCanInteract;

	UInteractTriggerComponent();

	UFUNCTION(BlueprintCallable, Category =  InteractComponent)
	void OnTriggerBeginOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	
};
