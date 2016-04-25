// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "EquipmentItem.h"

UEquipmentItem::UEquipmentItem(const FObjectInitializer& Initializer)
	:Super(Initializer)
{
	Slot = EEquipmentSlot::HEAD;
}

EEquipmentSlot UEquipmentItem::GetSlot()
{
	return Slot;
}
