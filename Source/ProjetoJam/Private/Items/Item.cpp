// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "Item.h"

UItem::UItem(const FObjectInitializer& Initializer)
	:Super(Initializer)
{
	Type = EItemType::CONSUMABLE;
	Descriptions = FItemDescriptions();
}

FItemDescriptions UItem::GetDescription()
{
	return Descriptions;
}

EItemType UItem::GetType()
{
	return Type;
}

