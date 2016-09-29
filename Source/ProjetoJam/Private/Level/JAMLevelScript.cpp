// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "FactionManager.h"
#include "StatementDatabase.h"
#include "JAMLevelScript.h"
#include "JAMGameInstance.h"
#include "AgentSpawner.h"

AJAMLevelScript::AJAMLevelScript()
{
	WorldStatements.Empty();
}

void AJAMLevelScript::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (OnAgentSpawned.IsBound())
	{
		OnAgentSpawned.Clear();
	}

	if (OnSaveGame.IsBound())
	{
		OnAgentSpawned.Clear();
	}
}

void AJAMLevelScript::InitializeWorldStatements()
{
	//TODO: CHECK IF IS LOADING LEVEL
	UJAMGameInstance* gameInst = Cast<UJAMGameInstance>(GetGameInstance());
	
	for (const FString& Statement : WorldStatements)
	{
		if (Statement != "")
		{
			gameInst->StatementDatabase->InsertIntoDatabaseWithString(Statement);
		}
		else
		{
			UE_LOG(DatabaseLog, Warning, TEXT("%s is trying to add a null statement to the database"), *GetName());
		}
	}
}

void AJAMLevelScript::LoadLevel()
{

}

void AJAMLevelScript::SpawnAgents()
{
	//TODO: Find the locations to spawn the special agents
	UJAMGameInstance* gameInst = Cast<UJAMGameInstance>(GetGameInstance());

	TArray<UStatement*> Statements;
	const FString key = "agents.";

	if (gameInst->StatementDatabase->FindStatements(key, Statements))
	{
		FDataTableRowHandle handle;
		handle.DataTable = LoadObject<UDataTable>(NULL, TEXT("/Game/Characters/AgentsData.AgentsData"), NULL, LOAD_None, NULL);
		check(handle.DataTable)

		static const FString ContextString(TEXT("GENERAL"));
		FAgentData* agentData;

		for (UStatement* statement : Statements)
		{
			handle.RowName = FName(*statement->LastVertex());
			agentData = handle.GetRow<FAgentData>(ContextString);
			check(agentData)

			const FString spawnerLocationKey = handle.RowName.ToString() + TEXT(".spawn_location!");
			UStatement* locationStatement = gameInst->StatementDatabase->FindExludingStatement(spawnerLocationKey);
			check(locationStatement)

			FName locationName = FName(*locationStatement->LastVertex());

			AAgentSpawner* spawner = UJamLibrary::FindSpawner(this, locationName);

			check(agentData->AgentBlueprint)

			if (spawner)
			{
				spawner->SetAgentToSpawnType(agentData->AgentBlueprint);
			}


		}

	}

	OnAgentSpawned.Broadcast();
}

void AJAMLevelScript::SaveGameState()
{
	OnSaveGame.Broadcast();
}
