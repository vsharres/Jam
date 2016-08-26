// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "Faction.h"


UFaction::UFaction(const FObjectInitializer& Initializer)
	:Super(Initializer)
{
	Status = FFactionStatus();
}

int32 UFaction::GetStatusToPlayer()
{
	return Status.StatusPlayer;
}

int32 UFaction::GetStatusToFaction(EFactionType type)
{
	int32 toReturn;

	switch (type)
	{

	case EFactionType::PLAYER:
		toReturn = Status.StatusPlayer;
		break;
	case EFactionType::FACTION1:
		toReturn = Status.StatusFaction1;
		break;
	case EFactionType::FACTION2:
		toReturn = Status.StatusFaction2;
		break;
	case EFactionType::FACTION3:
		toReturn = Status.StatusFaction3;
		break;
	default:
		toReturn = Status.StatusPlayer;
		break;
	}

	return toReturn;
}

void UFaction::InitializeFaction(EFactionType type)
{
	this->FactionType = type;
	ChangeRelationTo(type, 10);
}

void UFaction::ChangeRelationTo(EFactionType type, int32 value)
{
	switch (type)
	{

	case EFactionType::PLAYER:
		Status.StatusPlayer = value;
		break;
	case EFactionType::FACTION1:
		Status.StatusFaction1 =  value;
		break;
	case EFactionType::FACTION2:
		Status.StatusFaction2 = value;
		break;
	case EFactionType::FACTION3:
		Status.StatusFaction3 = value;
		break;
	default:
		Status.StatusPlayer = value;
		break;
	}

	Status.ClampValues();
}
