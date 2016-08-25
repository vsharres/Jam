// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Item.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8 {
	CONSUMABLE,
	EQUIPMENT,
	QUEST,
	MISC
};


USTRUCT(BlueprintType)
struct FItemDescriptions
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, Category = ItemDescriptionStruct)
		FText Name;

	UPROPERTY(EditAnywhere, Category = ItemDescriptionStruct)
		FText Description;

	FItemDescriptions()
	{
		Name = FText::FromString("FILL THE NAME");
		Description = FText::FromString("FILL THE DESCRIPTION");
	}


};

/**
 *
 */
UCLASS(BlueprintType, Blueprintable, Abstract)
class PROJETOJAM_API UItem : public UObject
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = Item)
		FItemDescriptions Descriptions;

	UPROPERTY(EditDefaultsOnly, Category = Item)
		EItemType Type;


public:

	UItem(const FObjectInitializer& Initializer);

	UFUNCTION(BlueprintPure, Category = Item)
		FItemDescriptions GetDescription();

	UFUNCTION(BlueprintPure, Category = Item)
		EItemType GetType();


};
