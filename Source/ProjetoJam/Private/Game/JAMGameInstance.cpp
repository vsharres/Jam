// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "JAMGameInstance.h"

UJAMGameInstance::UJAMGameInstance()
{

}

void UJAMGameInstance::Init()
{
	StatementDatabase = NewObject<UStatementDatabase>(GetWorld());
	StatementDatabase->InitializeDataBase();

	/*FactionManager = NewObject<UFactionManager>(GetWorld());
	FactionManager->InitializeFactions();*/
}
