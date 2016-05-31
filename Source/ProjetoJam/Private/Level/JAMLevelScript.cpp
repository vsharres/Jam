// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "JAMLevelScript.h"

void AJAMLevelScript::InitializeGame()
{
	OnDatabaseInit.Broadcast();
	OnAgentSpawned.Broadcast();
	OnAgentInit.Broadcast();
}

void AJAMLevelScript::SaveGameState()
{
	OnSaveGame.Broadcast();
}
