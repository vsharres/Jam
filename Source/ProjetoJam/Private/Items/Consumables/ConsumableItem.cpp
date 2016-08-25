// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "ConsumableItem.h"


UConsumableItem::UConsumableItem(const FObjectInitializer& Initializer)
	:Super(Initializer)
{
	Type = EItemType::CONSUMABLE;
}

void UConsumableItem::ConsumeItem()
{
	
}
