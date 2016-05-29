// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Public/Statement/StatementDatabase.h"
#include "Location.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LocationLog, Log, All);

UCLASS()
class PROJETOJAM_API ALocation : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, Category = Location)
		TArray<ALocation*> ChildLocations;

	UPROPERTY(VisibleAnywhere, Category = Trigger)
		USphereComponent* Trigger;
	
public:	

	/**The name of the Location. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Location)
		FString LocationName;

	// Sets default values for this actor's properties
	ALocation(const FObjectInitializer& Initializer);


	/**
	* Called to get the parent location.
	* @return The parent location pointer.
	*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Parent Location", Keywords = "Location Spawn"), Category = Location)
		TArray<ALocation*> GetChildLocations();

	/**
	* Called to check if a location is child to another.
	* @param NewLocationName - An const FString location name.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Is Location Child", Keywords = "Is Location Child"), Category = Location)
		bool IsLocationChild(ALocation* LocationToCompare);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION()
		void OnTriggerBeginOverlap(AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
		void OnTriggerEndOverlap(AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	
	
};
