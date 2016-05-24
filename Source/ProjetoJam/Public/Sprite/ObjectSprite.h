// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Sprite/FadableSpriteActor.h"
#include "ObjectSprite.generated.h"

/**
 * 
 */
UCLASS()
class PROJETOJAM_API AObjectSprite : public AFadableSpriteActor
{
	GENERATED_BODY()
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collider)
		UBoxComponent* Collider;

public:
		AObjectSprite(const FObjectInitializer& ObjectInitializer);
	
	
};
