// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "PlayerAgent.h"
#include "FadableSpriteActor.h"


AFadableSpriteActor::AFadableSpriteActor(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	FadeOutTimeline = ObjectInitializer.CreateDefaultSubobject<UTimelineComponent>(this, TEXT("FadeInTimeline"));
	FadeOutTimeline->SetTickableWhenPaused(false);
	
	FadeOutFunction.BindUFunction(this, FName(TEXT("FadeInTimelineCallback")));
}

void AFadableSpriteActor::FadeOutTimelineCallback()
{
	
}

void AFadableSpriteActor::CameraTimelineCallback()
{
	const FVector Start = Player->GetCamera()->GetComponentLocation();
	const FVector End = Player->GetActorLocation();

	FHitResult HitData(ForceInit);

	if (UJamLibrary::Trace(GetWorld(), this, Start, End, HitData))
	{
		if (HitData.GetActor()->Implements<UObjectFade>())
		{
			Cast<IObjectFade>(HitData.GetActor())->FadeOut();
		}
	}
}

void AFadableSpriteActor::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<APlayerAgent>(UGameplayStatics::GetPlayerCharacter(this, 0));

	FadeOutTimeline->AddEvent(1.0f, FadeOutFunction);

}

void AFadableSpriteActor::FadeIn()
{
	
}

void AFadableSpriteActor::FadeOut()
{
	FadeOutTimeline->Play();
}
