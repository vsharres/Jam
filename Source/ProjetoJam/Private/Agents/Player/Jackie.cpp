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
}


