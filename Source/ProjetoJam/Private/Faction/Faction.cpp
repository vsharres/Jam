// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "Faction.h"


UFaction::UFaction(const FObjectInitializer& Initializer)
	:Super(Initializer)
{

}

int32 UFaction::GetStatusToPlayer()
{
	return Status.StatusPlayer;
}

int32 UFaction::GetStatusToFaction(EFactionNames name)
{
	int32 toReturn;

	switch (name)
	{

	case EFactionNames::PLAYER:
		toReturn = Status.StatusPlayer;
		break;
	case EFactionNames::FACTION1:
		toReturn = Status.StatusFaction1;
		break;
	case EFactionNames::FACTION2:
		toReturn = Status.StatusFaction2;
		break;
	case EFactionNames::FACTION3:
		toReturn = Status.StatusFaction3;
		break;
	default:
		toReturn = Status.StatusPlayer;
		break;
	}

	return toReturn;
}

void UFaction::InitializeFaction(EFactionNames name)
{
	this->FactionName = name;

	ChangeRelationTo(name, 10);

}

void UFaction::ChangeRelationTo(EFactionNames name, int32 value)
{
	switch (name)
	{

	case EFactionNames::PLAYER:
		Status.StatusPlayer = value;
		break;
	case EFactionNames::FACTION1:
		Status.StatusFaction1 =  value;
		break;
	case EFactionNames::FACTION2:
		Status.StatusFaction2 = value;
		break;
	case EFactionNames::FACTION3:
		Status.StatusFaction3 = value;
		break;
	default:
		Status.StatusPlayer = value;
		break;
	}

	Status.ClampValues();
}
