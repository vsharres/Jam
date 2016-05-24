// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "ObjectSprite.h"

AObjectSprite::AObjectSprite(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Collider = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, "BoxCollider");
	Collider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Collider->SetCollisionObjectType(ECC_WorldStatic);
	Collider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	Collider->SetCollisionResponseToChannel(COLLISION_FADEOBJECT, ECollisionResponse::ECR_Overlap);
	Collider->SetBoxExtent(FVector(50.0f, 50.0f, 100.0f));
	//Collider->SetRelativeRotation(ISOMETRIC_ROTATION);

	Collider->AttachTo(RootComponent);

	GetSprite()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetSprite()->bGenerateOverlapEvents = false;
	GetSprite()->SetRelativeRotation(ISOMETRIC_ROTATION);

}
