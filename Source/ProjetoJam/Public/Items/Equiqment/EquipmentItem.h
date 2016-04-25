// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Items/Item.h"
#include "EquipmentItem.generated.h"

UENUM(BlueprintType)
enum class EEquipmentSlot : uint8
{
	HEAD,
	TORSO,
	ARMS,
	LEGS,
	WEAPON
};


USTRUCT(BlueprintType)
struct FEquipmentStats
{
		GENERATED_USTRUCT_BODY()

public:

	UPROPERTY()
		int32 HealthToAdd;


			FEquipmentStats()
		{}

};

/**
 * 
 */
UCLASS()
class PROJETOJAM_API UEquipmentItem : public UItem
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = Equipment)
		EEquipmentSlot Slot;

public:

	UEquipmentItem(const FObjectInitializer& Initializer);

	UFUNCTION(BlueprintPure, Category = Equipment)
		EEquipmentSlot GetSlot();
	
	
};
