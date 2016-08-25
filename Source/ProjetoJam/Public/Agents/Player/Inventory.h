// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Items/Item.h"
#include "Inventory.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PROJETOJAM_API UInventory : public UObject
{
	GENERATED_BODY()

private:
	TMap<FName, UEquipmentItem*> Equipment;

	TMap<FName, UConsumableItem*> Consumables;

	TMap<FName, UQuestItem*> QuestItems;


public:

	UPROPERTY(BlueprintReadWrite, Category = Inventory)
		int32 Coins;

	UInventory();

	UFUNCTION(BlueprintPure, Category = Inventory)
		TArray<UEquipmentItem*> GetEquimentArray();

	UFUNCTION(BlueprintPure, Category = Inventory)
		TArray<UConsumableItem*> GetConsumablesArray();

	UFUNCTION(BlueprintPure, Category = Inventory)
		TArray<UQuestItem*> GetQuestItemsArray();

	UFUNCTION(BlueprintCallable, Category = Inventory)
		void AddToInventory(UItem* NewItem);

	UFUNCTION(BlueprintCallable, Category = Inventory)
		bool RemoveKeyFromInventory(const FName& key, EItemType ItemType);

	UFUNCTION(BlueprintPure, Category = Inventory)
		bool HasItemKey(const FName& key, EItemType Type);

	FORCEINLINE static bool ConstPredicate(const FName& key1, const FName& key2)
	{
		return (key1 < key2);
	}
	
};
