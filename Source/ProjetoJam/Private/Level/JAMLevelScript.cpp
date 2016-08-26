// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "FactionManager.h"
#include "JAMLevelScript.h"

void AJAMLevelScript::InitializeGame()
{
	LoadLevel();

	OnAgentSpawned.Broadcast();
	OnAgentInit.Broadcast();
}

void AJAMLevelScript::SaveGameState()
{
	OnSaveGame.Broadcast();
}

void AJAMLevelScript::LoadLevel()
{
	InitializeManagers();

}

void AJAMLevelScript::InitializeManagers()
{
	Database = NewObject<UStatementDatabase>(this, "Statement Database");
	FactionManager = NewObject<UFactionManager>(this, "Faction Manager");

	Database->InitializeDataBase();
	FactionManager->InitializeFactions();
}
