// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "AgentController.h"
#include "Action.h"
#include "BrainComponent.h"
#include "Agent.h"
#include "Practice.h"

AAgentController::AAgentController()
{
	Database = UJamLibrary::GetStatementDatabase(this);
	PossibleActions.Empty();
}

FName AAgentController::GetAgentName()
{
	AAgent* agent = Cast<AAgent>(GetPawn());

	return agent->GetAgentName();
}

void AAgentController::QueryDatabase()
{
	if (!Database->IsValidLowLevelFast(false))
	{
		UE_LOG(DatabaseLog, Error, TEXT("Database in the %s controller"), *GetName());
		return;
	}

	const FString queryKey = "practice." + GetAgentName().ToString();

	TArray<UStatement*> foundPractices;
	
	Database->FindStatements(queryKey, foundPractices);

	if (foundPractices.Num() > 0)
	{
		TArray<UAction*> foundActions;

		for (UStatement* practice : foundPractices)
		{
			UPractice* temp = Cast<UPractice>(practice);

			if (temp)
			{
				temp->AddToActionsArray(foundActions);
			}
		}

	}

}

void AAgentController::StopBehavior()
{
	GetBrainComponent()->StopLogic("Finished Behavior");
}

void AAgentController::BeginPlay()
{
	if (CurrentAction)
	{
		CurrentAction->StartAction();
	}

	Super::BeginPlay();
}
