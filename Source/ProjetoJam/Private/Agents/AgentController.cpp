// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "AgentController.h"
#include "Action.h"
#include "BrainComponent.h"
#include "Agent.h"
#include "Practice.h"

AAgentController::AAgentController()
{
	PossibleActions.Empty();
}

FName AAgentController::GetAgentName()
{
	AAgent* agent = Cast<AAgent>(GetPawn());

	return agent->GetAgentName();
}

void AAgentController::QueryDatabase()
{
	PossibleActions.Empty(1);

	if (!Database->IsValidLowLevelFast(false))
	{
		UE_LOG(DatabaseLog, Error, TEXT("Database in the %s controller"), *GetName());
		return;
	}

	const FString queryKey = "practice." + GetAgentName().ToString() + ".";

	TArray<UStatement*> foundPractices;

	Database->FindStatements(queryKey, foundPractices);

	if (foundPractices.Num() > 0)
	{
		for (UStatement* practice : foundPractices)
		{
			UPractice* temp = Cast<UPractice>(practice);

			if (temp)
			{
				temp->AddToActionsArray(PossibleActions, this);
			}
		}


	}

	ChooseAction();

}

void AAgentController::ChooseAction()
{
	//TODO: Compare all possible actions to figure out which is the better action to perform
	if (!CurrentAction->IsValidLowLevelFast())
	{
		if (PossibleActions.Num() > 0)
		{
			CurrentAction = PossibleActions[0];
			CurrentAction->StartAction();
		}
	}
}

void AAgentController::FinishBehavior()
{
	GetBrainComponent()->StopLogic("Finished Behavior");
	QueryDatabase();

}

void AAgentController::BeginPlay()
{
	QueryDatabase();

	if (CurrentAction)
	{
		CurrentAction->StartAction();
	}

	Super::BeginPlay();
}

void AAgentController::PostInitializeComponents()
{
	Database = UJamLibrary::GetStatementDatabase(this);

	if (Database)
	{
		Database->OnDatabaseUpdated.AddDynamic(this, &AAgentController::QueryDatabase);
	}

	Super::PostInitializeComponents();
}
