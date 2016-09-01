// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "FactionManager.h"
#include "StatementDatabase.h"
#include "JAMLevelScript.h"
#include "JAMGameInstance.h"
#include "AgentSpawner.h"

AJAMLevelScript::AJAMLevelScript()
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
		handle.DataTable = LoadObject<UDataTable>(NULL, TEXT("/Game/Databases/Agents/AgentsData.AgentsData"), NULL, LOAD_None, NULL);
		check(handle.DataTable)

		static const FString ContextString(TEXT("GENERAL"));
		FAgentData* agentData;

		for (UStatement* statement : Statements)
		{
			handle.RowName = FName(*statement->LastVertex());
			agentData = handle.GetRow<FAgentData>(ContextString);
			check(agentData)

			const FString spawnerLocationKey = handle.RowName.ToString() + ".spawn_location!";
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
