// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "Action.h"
#include "AgentController.h"

UAction::UAction(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Caller = nullptr;
}

UAction* UAction::InstantiateAction(AAgentController* agentCaller)
{
	UAction* action = NewObject<UAction>();
	action->Caller = agentCaller;
	
	return action;
}

void UAction::StartAction()
{
	if (ActionBT.IsValid())
	{
		UBehaviorTree* Tree = ActionBT.Get();	
		Caller->RunBehaviorTree(Tree);
	}
}

void UAction::StopAction()
{
	Caller->StopBehavior();
}

void UAction::ExecutePostConditions_Implementation()
{

}

bool UAction::CheckPreConditions_Implementation()
{



	return true;
}
