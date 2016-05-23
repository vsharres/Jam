// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperSpriteActor.h"
#include "ObjectFade.h"
#include "FadableSpriteActor.generated.h"

class APlayerAgent;

/**
 * 
 */
UCLASS()
class PROJETOJAM_API AFadableSpriteActor : public APaperSpriteActor, public IObjectFade
{
	GENERATED_BODY()
private:

	UPROPERTY()
		APlayerAgent* Player;

	UPROPERTY()
	UTimelineComponent* FadeOutTimeline;

	UPROPERTY()
	UTimelineComponent* CameraTraceTimeline;

	FOnTimelineEvent FadeOutFunction{};

	FOnTimelineEvent CameraTraceFunction{};

public:

	AFadableSpriteActor(const FObjectInitializer& ObjectInitializer);

	UFUNCTION()
		void FadeOutTimelineCallback();

	UFUNCTION()
		void CameraTimelineCallback();

	void BeginPlay() override;

	 void FadeIn() override;

	 void FadeOut() override;
	
};
