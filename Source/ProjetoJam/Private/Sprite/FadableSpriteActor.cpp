// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "PlayerAgent.h"
#include "FadableSpriteActor.h"


AFadableSpriteActor::AFadableSpriteActor(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	Root = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, "SpriteActor");
	RootComponent = Root;

	Sprite = ObjectInitializer.CreateDefaultSubobject<UPaperSpriteComponent>(this, "Sprite");
	Sprite->SetCollisionResponseToChannel(COLLISION_FADEOBJECT, ECollisionResponse::ECR_Overlap);
	Sprite->AttachTo(Root);

	CameraTraceTimeline = ObjectInitializer.CreateDefaultSubobject<UTimelineComponent>(this, "CameraTimeline");
	CameraTraceTimeline->SetTickableWhenPaused(false);
	CameraTraceTimeline->SetTimelineLengthMode(TL_TimelineLength);
	CameraTraceTimeline->SetTimelineLength(1.0f);
	CameraTraceTimeline->SetLooping(true);

	CameraTraceFunction.BindUFunction(this,"CameraTimelineCallback");

	bFaded = false;

}

void AFadableSpriteActor::CameraTimelineCallback()
{
	const FVector Start = Player->GetCamera()->GetComponentLocation();
	const FVector End = Player->GetActorLocation();

	TArray<FHitResult> Hits;
	FVector HitPos;

	if (UJamLibrary::TraceSphere(GetWorld(), Player, Start, End, Player->GetActorRotation(), TRACE_SPHERERADIUS_DEFAULT, Hits,COLLISION_FADEOBJECT))
	{
		for (const auto& Hit : Hits)
		{
			if (Hit.GetActor() == this)
			{
				return;
			}
		}

	}
	
	CameraTraceTimeline->Stop();
	FadeIn();
	
}

UPaperSpriteComponent* AFadableSpriteActor::GetSprite()
{
	return Sprite;
}

void AFadableSpriteActor::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<APlayerAgent>(UGameplayStatics::GetPlayerCharacter(this, 0));

	CameraTraceTimeline->AddEvent(0.0f, CameraTraceFunction);

}

void AFadableSpriteActor::FadeIn(const FVector2D& UVPos)
{
	if (bFaded)
	{
		bFaded = false;
		UMaterialInstanceDynamic* MID;
		MID = GetSprite()->CreateDynamicMaterialInstance(0);

		if (MID && GetWorld())
		{
			MID->SetScalarParameterValue("Start_Time_FadeIn", GetWorld()->GetTimeSeconds());
		}
			
	}
}

void AFadableSpriteActor::FadeOut(const FVector2D& UVPos)
{
	if (!bFaded)
	{
		bFaded = true;
		UMaterialInstanceDynamic* MID;
		MID = GetSprite()->CreateDynamicMaterialInstance(0);

		if (MID && GetWorld())
		{
			MID->SetScalarParameterValue("Start_Time_FadeOut", GetWorld()->GetTimeSeconds());
		}

		CameraTraceTimeline->PlayFromStart();
		
	}
}
