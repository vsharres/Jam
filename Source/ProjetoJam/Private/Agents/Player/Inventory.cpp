// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "Inventory.h"
#include "Items/Consumables/ConsumableItem.h"
#include "Items/Equiqment/EquipmentItem.h"
#include "Items/Quest/QuestItem.h"

UInventory::UInventory()
{
	Equipment.Empty();
	Consumables.Empty();
	QuestItems.Empty();

	Coins = 0;
}


TArray<UEquipmentItem*> UInventory::GetEquimentArray()
{
	TArray<UEquipmentItem*> arrayToReturn;
	Equipment.GenerateValueArray(arrayToReturn);

	return arrayToReturn;
}

TArray<UConsumableItem*> UInventory::GetConsumablesArray()
{
	TArray<UConsumableItem*> arrayToReturn;
	Consumables.GenerateValueArray(arrayToReturn);

	return arrayToReturn;
}

TArray<UQuestItem*> UInventory::GetQuestItemsArray()
{
	TArray<UQuestItem*> arrayToReturn;
	QuestItems.GenerateValueArray(arrayToReturn);

	return arrayToReturn;
}

void UInventory::AddToInventory(UItem* NewItem)
{
	if (NewItem->IsValidLowLevelFast())
	{
		switch (NewItem->GetType())
		{
		case EItemType::CONSUMABLE:
			Consumables.Add(NewItem->GetFName(), Cast<UConsumableItem>(NewItem));
			Consumables.KeySort(ConstPredicate);
			break;
		case  EItemType::EQUIPMENT:
			Equipment.Add(NewItem->GetFName(), Cast<UEquipmentItem>(NewItem));
			Equipment.KeySort(ConstPredicate);
			break;
		case EItemType::QUEST:
			QuestItems.Add(NewItem->GetFName(), Cast<UQuestItem>(NewItem));
			QuestItems.KeySort(ConstPredicate);
			break;
		case EItemType::MISC:
			break;
		default:
			break;
		}
	}
}

bool UInventory::RemoveKeyFromInventory(const FName& key, EItemType ItemType)
{

	int32 numDel = 0;

	switch (ItemType)
	{
	case EItemType::CONSUMABLE:
		numDel = Consumables.Remove(key);
		Consumables.KeySort(ConstPredicate);
		break;
	case EItemType::EQUIPMENT:
		numDel = Equipment.Remove(key);
		Equipment.KeySort(ConstPredicate);
		break;
	case  EItemType::QUEST:
		numDel = QuestItems.Remove(key);
		QuestItems.KeySort(ConstPredicate);
		break;
	case EItemType::MISC:
		break;
	default:
		break;
	}

	return (numDel > 0);

}


bool UInventory::HasItemKey(const FName& key, EItemType Type)
{
	bool hasKey = false;

	switch (Type)
	{
	case EItemType::CONSUMABLE:
		hasKey = Consumables.Contains(key);
		Consumables.KeySort(ConstPredicate);
		break;
	case EItemType::EQUIPMENT:
		hasKey = Equipment.Contains(key);
		Equipment.KeySort(ConstPredicate);
		break;
	case  EItemType::QUEST:
		hasKey = QuestItems.Contains(key);
		QuestItems.KeySort(ConstPredicate);
		break;
	case EItemType::MISC:
		break;
	default:
		break;
	}

	return hasKey;
}

