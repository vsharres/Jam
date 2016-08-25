// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoJam.h"
#include "Inventory.h"
#include "Interact.h"
#include "ObjectFade.h"
#include "Public/Agents/Player/PlayerAgent.h"

APlayerAgent::APlayerAgent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Stats.Speed = 0.35f;
	CameraBoom = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("CameraBoom"));
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->SetWorldRotation(FRotator(0, 330, 270));
	FAttachmentTransformRules Rules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, false);
	CameraBoom->AttachToComponent(RootComponent,Rules);


	Camera = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("Camera"));
	Camera->ProjectionMode = ECameraProjectionMode::Orthographic;
	Camera->OrthoWidth = 1024;

	Camera->AttachToComponent(CameraBoom, Rules);

	CameraTraceTimeline = ObjectInitializer.CreateDefaultSubobject<UTimelineComponent>(this, TEXT("CameraTraceTimeline"));
	CameraTraceTimeline->SetTickableWhenPaused(false);
	CameraTraceTimeline->SetTimelineLength(1.0f);
	CameraTraceTimeline->SetLooping(true);

	EventFunction.BindUFunction(this, FName{ TEXT("CameraTraceTimelineCallback") });

	Agent_Type = EAgentType::PLAYER;
	Agent_Name = "Lied";
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

void APlayerAgent::CameraTraceTimelineCallback()
{
	const FVector Start = Camera->GetComponentLocation();
	const FVector End = GetActorLocation();

	TArray<FHitResult> Hits;

	if (UJamLibrary::TraceSphere(GetWorld(), this, Start, End, GetActorRotation(), TRACE_SPHERERADIUS_DEFAULT, Hits, COLLISION_FADEOBJECT))
	{
		for (const auto& hit : Hits)
		{
			if (hit.GetActor()->Implements<UObjectFade>())
			{
				Cast<IObjectFade>(hit.GetActor())->FadeOut();
			}
		}
	
	}
	
}


void APlayerAgent::BeginPlay()
{
	Super::BeginPlay();

	CameraTraceTimeline->AddEvent(1.0f, EventFunction);
	CameraTraceTimeline->Play();
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

