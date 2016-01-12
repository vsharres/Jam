// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoJam.h"
#include "Public/Agents/Player/Jackie.h"

AJackie::AJackie(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CameraBoom = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("CameraBoom"));
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->SetWorldRotation(FRotator(0, 330, 270));
	CameraBoom->AttachTo(RootComponent);


	Camera = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("Camera"));
	Camera->ProjectionMode = ECameraProjectionMode::Orthographic;
	Camera->OrthoWidth = 1024;

	Camera->AttachTo(CameraBoom);

	Inventory.Empty();

	Agent_Type = EAgentType::PLAYER;
	Agent_Name = "Jackie";
}

UCameraComponent* AJackie::GetCamera()
{
	return Camera;
}

void AJackie::MoveRight(float input)
{
	Super::MoveRight(input);
}

void AJackie::MoveUp(float input)
{
	Super::MoveUp(input);
}

void AJackie::InitializeAgent()
{

}

void AJackie::SetupPlayerInputComponent(UInputComponent * InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("MoveUp", this, &AJackie::MoveUp);
	InputComponent->BindAxis("MoveRight", this, &AJackie::MoveRight);
}

