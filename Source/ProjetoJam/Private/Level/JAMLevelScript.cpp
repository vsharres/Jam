// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "FactionManager.h"
#include "StatementDatabase.h"
#include "JAMLevelScript.h"

AJAMLevelScript::AJAMLevelScript()
{
}

void AJAMLevelScript::InitializeGame()
{
	OnAgentSpawned.Broadcast();
}

void AJAMLevelScript::SaveGameState()
{
	OnSaveGame.Broadcast();
}
