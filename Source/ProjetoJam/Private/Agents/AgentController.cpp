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
	QueryCooldown = 0.0f;
	QueryTimer = 1.0f;

}

FName AAgentController::GetAgentName()
{
	AAgent* agent = Cast<AAgent>(GetPawn());

	return agent->GetAgentName();
}

void AAgentController::QueryDatabase()
{
	if (!FMath::IsNearlyZero(QueryCooldown) || GetWorld()->GetRealTimeSeconds() - QueryCooldown < QueryTimer)
	{
		QueryCooldown = GetWorld()->GetRealTimeSeconds();
		return;
	}

	QueryCooldown = GetWorld()->GetRealTimeSeconds();
	PossibleActions.Empty(1);

	if (!Database->IsValidLowLevelFast(false))
	{
		UE_LOG(DatabaseLog, Error, TEXT("Database in the %s controller"), *GetName());
		return;
	}

	const FString queryKey = TEXT("practice.") + GetAgentName().ToString() + ".";

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
	GetBrainComponent()->StopLogic(TEXT("Finished Behavior"));
	QueryDatabase();

}

void AAgentController::BeginPlay()
{
	Super::BeginPlay();

	QueryDatabase();
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
