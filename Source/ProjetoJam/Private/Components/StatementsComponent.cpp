// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "StatementsComponent.h"


// Sets default values for this component's properties
UStatementsComponent::UStatementsComponent(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;
	bAutoRegister = true;
	bAutoActivate = true;

}

// Called when the game starts
void UStatementsComponent::BeginPlay()
{
	Super::BeginPlay();
	Database = UJamLibrary::GetStatementDatabase(this);
	check(Database)

	AddStatementsToDatabase();
	
}

void UStatementsComponent::AddStatementsToDatabase()
{
	for (const FString& Statement : Statements)
	{
		Database->InsertIntoDatabaseWithString(RootName + Statement);		
	}
}

