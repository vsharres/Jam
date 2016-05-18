// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoJam.h"
#include "Inventory.h"
#include "Interact.h"
#include "Public/Agents/Player/PlayerAgent.h"

APlayerAgent::APlayerAgent(const FObjectInitializer& ObjectInitializer)
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

	Agent_Type = EAgentType::PLAYER;
	Agent_Name = "Jackie";
	bCanInteract = false;
}

AActor* APlayerAgent::GetCurInteractingActor()
{
	return ActorToInteract.Get();
}

void APlayerAgent::SetCurInteractingActor(AActor* Interactor)
{
	ActorToInteract = Interactor;
}

UCameraComponent* APlayerAgent::GetCamera()
{
	return Camera;
}

UInventory* APlayerAgent::GetInventory()
{
	return Inventory;
}

void APlayerAgent::InteractWith()
{
	if (bCanInteract && ActorToInteract.IsValid() && ActorToInteract->Implements<UInteract>())
	{
		Cast<IInteract>(ActorToInteract.Get())->Interact();
	}
}

void APlayerAgent::MoveRight(float input)
{
	Super::MoveRight(input);
}

void APlayerAgent::MoveUp(float input)
{
	Super::MoveUp(input);
}

void APlayerAgent::InitializeAgent()
{
	Inventory = NewObject<UInventory>(this);
}

void APlayerAgent::UpdateFlipbook()
{
	Super::UpdateFlipbook();
}

void APlayerAgent::Kill()
{

}

void APlayerAgent::SetupPlayerInputComponent(UInputComponent * InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("MoveUp", this, &APlayerAgent::MoveUp);
	InputComponent->BindAxis("MoveRight", this, &APlayerAgent::MoveRight);

	InputComponent->BindAction("Interact", IE_Pressed, this, &APlayerAgent::InteractWith);

}

