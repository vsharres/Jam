// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "Action.h"

UAction::UAction()
{
	Caller = nullptr;
	ActionBT = nullptr;
	ActionStatementPreset = FStatement();
}

void UAction::ExecutePostConditions_Implementation()
{

}

bool UAction::CheckPreConditions_Implementation()
{
	return true;
}
