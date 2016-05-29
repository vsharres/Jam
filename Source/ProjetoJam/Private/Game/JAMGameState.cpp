// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "JAMGameState.h"

void AJAMGameState::BeginPlay()
{
	OnDatabaseInit.Broadcast();
	OnAgentSpawned.Broadcast();
	OnAgentInit.Broadcast();

	Super::BeginPlay();

}

void AJAMGameState::SaveGameState()
{
	OnSaveGame.Broadcast();
}
