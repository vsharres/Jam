// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "ObjectSprite.h"

AObjectSprite::AObjectSprite(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	TileSize = ETileSize::L1W1;

	Collider = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, "BoxCollider");
	Collider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Collider->SetCollisionObjectType(ECC_WorldStatic);
	Collider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	Collider->SetCollisionResponseToChannel(COLLISION_FADEOBJECT, ECollisionResponse::ECR_Overlap);
	Collider->SetBoxExtent(TILE_L1W1_EXTENT);
	//Collider->SetRelativeRotation(ISOMETRIC_ROTATION);

	FAttachmentTransformRules Rules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, false);
	Collider->AttachToComponent(RootComponent,Rules);

	GetSprite()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetSprite()->bGenerateOverlapEvents = false;
	GetSprite()->SetRelativeRotation(ISOMETRIC_ROTATION);

}

ETileSize AObjectSprite::GetTileSize()
{
	return TileSize;
}

void AObjectSprite::SetTileSize(ETileSize newSize)
{
	switch (newSize)
	{
	case ETileSize::L1W1:
		Collider->SetBoxExtent(TILE_L1W1_EXTENT);
		break;
	case ETileSize::L2W1:
		Collider->SetBoxExtent(TILE_L2W1_EXTENT);
		break;
	case ETileSize::L2W2:
		Collider->SetBoxExtent(TILE_L2W2_EXTENT);
		break;
	default:
		Collider->SetBoxExtent(TILE_L1W1_EXTENT);
		break;
	}

	TileSize = newSize;
}

#if WITH_EDITOR

void AObjectSprite::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if ((PropertyName == GET_MEMBER_NAME_CHECKED(AObjectSprite, TileSize)))
	{
		SetTileSize(TileSize);
	}
}

#endif
