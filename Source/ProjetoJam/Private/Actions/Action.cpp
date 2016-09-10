// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "Action.h"
#include "AgentController.h"

UAction::UAction(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	ParentPractice = nullptr;
	bIsActive = false;
}

void UAction::InstantiateAction(UPractice* practice, AAgentController* agentCaller)
{
	ParentPractice = practice;
	Caller = agentCaller;
}

void UAction::StartAction()
{	
	if (!bIsActive)
	{
		bIsActive = true;
		UBehaviorTree* Tree = ActionBT.LoadSynchronous();
		check(Tree)
		InitializeBlackBoard();
		Caller->RunBehaviorTree(Tree);
	}

}

void UAction::StopAction()
{
	bIsActive = false;
	Caller->FinishBehavior();
	ConditionalBeginDestroy();
}

void UAction::InitializeBlackBoard_Implementation()
{
	//Initialize the blackboard values
}

void UAction::ExecutePostConditions_Implementation()
{
	//TODO: WRITE THE POST CONDITIONS ON THE DATABASE
	StopAction();
}

bool UAction::CheckPreConditions_Implementation()
{
	return true;
}
