// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/BoxComponent.h"
#include "LocationComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJETOJAM_API ULocationComponent : public UBoxComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
		class AAgentSpawner* ParentSpawner;

	UPROPERTY()
		class UStatementDatabase* Database;
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
	class AAgentSpawner* ParentLocation;

	ULocationComponent();

	void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Location")
		void OnTriggerBeginOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	UFUNCTION(BlueprintCallable, Category = "Location")
		void OnTriggerEndOverlap(class UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
