// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "FactionManager.h"
#include "StatementDatabase.h"
#include "JAMLevelScript.h"

AJAMLevelScript::AJAMLevelScript()
{
	StatementDatabase = NewObject<UStatementDatabase>(this, "Statement Database");
	StatementDatabase->InitializeDataBase();

	FactionManager = NewObject<UFactionManager>(this, "Faction Manager");
	FactionManager->InitializeFactions();
}

void AJAMLevelScript::InitializeGame()
{
	SpawnAgents();
}

void AJAMLevelScript::SaveGameState()
{
	OnSaveGame.Broadcast();
}


void AJAMLevelScript::SpawnAgents()
{
	OnAgentSpawned.Broadcast();
}
