// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoJam.h"
#include "PaperFlipbookComponent.h"
#include "Public/Agents/Agent.h"


AAgent::AAgent(const class FObjectInitializer& Initializer)
	: Super(Initializer)
{
	Stats = FAgentStats();
	Agent_Type = EAgentType::GRUNT;
	
}

void AAgent::BeginPlay()
{
	Super::BeginPlay();

	Database_Ref = AStatementDatabase::GetStatementDatabase(this);
}

void AAgent::InitializeAgent()
{

}

void AAgent::MoveRight(float input)
{
	GetCharacterMovement()->AddInputVector(FVector(input, 0, 0));
}

void AAgent::MoveUp(float input)
{
	GetCharacterMovement()->AddInputVector(FVector(0, input, 0));
}

