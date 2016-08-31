// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "Practice.h"
#include "Action.h"

UPractice::UPractice(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

UPractice* UPractice::NewPractice(UObject* WorldContextObject, const FString& newStatementString, TSubclassOf<UPractice> practiceAsset)
{
	if (newStatementString == "") //warning message that a statement cannot be initialized with an empty string.
	{
		UE_LOG(StatementLog, Warning, TEXT("Can not initialize a statement with a empty string."));
		return NULL;
	}
	else if (!newStatementString.Contains(".") && !newStatementString.Contains("!")) //warning that a statement cannot have only the root vertex.
	{
		UE_LOG(StatementLog, Warning, TEXT("A statement can not have only the root vertex, it must have at least two vertices."));
		return NULL;
	}

	UPractice* newPractice = NewObject<UPractice>(WorldContextObject,practiceAsset);

	newPractice->Statement = newStatementString; //set the text property to the string input.

												  /*Temporary string for creating the vertices. */
	FString temp = "";

	/*for each character in the input string, add that character to the temporary string variable,
	then when finds one of the edge characters, add the resulting string to the vertices array,
	and that edge to the edges array.*/
	for (int32 index = 0; index < newStatementString.Len(); index++)
	{
		if (newStatementString[index] == '.') //for edges with the "." inclusion identifier.
		{
			newPractice->Edges.Add(".");
			newPractice->Vertices.Add(temp);
			temp = "";

		}
		else if (newStatementString[index] == '!') //for edges with the "!" exclusion identifier
		{
			newPractice->Edges.Add("!");
			newPractice->Vertices.Add(temp);
			temp = "";
		}
		else
		{
			temp += newStatementString[index];
		}
	}

	if (temp != "") //this last if is to add the last vertex in the statement, since there is no more edges to be found.
	{
		newPractice->Vertices.Add(temp);
	}

	//Generate the key to the statement.
	newPractice->GenerateKey();

	return newPractice;

}

void UPractice::AddToActionsArray(TArray<UAction*>& InActions, AAgentController* agentCaller)
{
	if (ActionsRef.Num() == 0)
	{
		return;
	}	

	UAction* newAction;

	for (int32 index = 0; index < ActionsRef.Num();index++)
	{
		newAction = NewObject<UAction>(this, ActionsRef[index]);

		if (newAction && !InActions.ContainsByPredicate([&](UAction* n) { return newAction->GetStatementKey() == n->GetStatementKey();}))
		{
			if (newAction->CheckPreConditions())
			{
				newAction->InstantiateAction(this, agentCaller);
				InActions.Add(newAction);
			}
		}
	}

}
