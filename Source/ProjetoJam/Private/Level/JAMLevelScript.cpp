// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "FactionManager.h"
#include "StatementDatabase.h"
#include "JAMLevelScript.h"

void AJAMLevelScript::InitializeGame()
{
	LoadLevel();
}

void AJAMLevelScript::SaveGameState()
{
	OnSaveGame.Broadcast();
}

void AJAMLevelScript::LoadLevel()
{
	InitializeManagers();
	SpawnAgents();

}

void AJAMLevelScript::InitializeManagers()
{
	StatementDatabase = NewObject<UStatementDatabase>(this, "Statement Database");
	StatementDatabase->InitializeDataBase();

	FactionManager = NewObject<UFactionManager>(this, "Faction Manager");
	FactionManager->InitializeFactions();
}

void AJAMLevelScript::SpawnAgents()
{
	OnAgentSpawned.Broadcast();
}
