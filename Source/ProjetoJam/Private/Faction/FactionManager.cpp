// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "FactionManager.h"
#include "Faction.h"


UFactionManager::UFactionManager(const FObjectInitializer& Initializer)
	:Super(Initializer)
{
	Factions.Empty();
}

TArray<UFaction*> UFactionManager::GetFactions()
{
	return Factions;
}
