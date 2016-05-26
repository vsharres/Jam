// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "ObjectFade.h"
#include "FadableSprite.generated.h"

class APlayerAgent;

/**
 * 
 */
UCLASS()
class PROJETOJAM_API AFadableSprite : public AActor, public IObjectFade
{
	GENERATED_BODY()
protected:

	UPROPERTY()
		APlayerAgent* Player;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Root)
		USceneComponent* Root;

	UPROPERTY()
	UTimelineComponent* CameraTraceTimeline;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Sprite)
		UPaperSpriteComponent* Sprite;

	UPROPERTY()
		bool bFaded;

	FOnTimelineEvent CameraTraceFunction{};

public:

	AFadableSprite(const FObjectInitializer& ObjectInitializer);

	UFUNCTION()
		void CameraTimelineCallback();

	UFUNCTION(BlueprintPure, Category = Sprite)
		UPaperSpriteComponent* GetSprite();

	void BeginPlay() override;

	 void FadeIn(const FVector2D& UVPos = FVector2D::ZeroVector) override;

	 void FadeOut(const FVector2D& UVPos = FVector2D::ZeroVector) override;
	
};
