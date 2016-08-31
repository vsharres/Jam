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
	if (ActionBT.IsValid())
	{
		bIsActive = true;
		UBehaviorTree* Tree = ActionBT.Get();	
		Caller->RunBehaviorTree(Tree);
	}

}

void UAction::StopAction()
{
	bIsActive = false;
	Caller->FinishBehavior();
	BeginDestroy();
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
