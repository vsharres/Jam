// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ObjectFade.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI, Blueprintable, meta = (CannotImplementInterfaceInBlueprint))
class UObjectFade : public UInterface
{
	GENERATED_UINTERFACE_BODY()
		
	
};


class IObjectFade
{
	GENERATED_IINTERFACE_BODY()

		UFUNCTION()
		virtual void FadeIn(const FVector2D& UVPos= FVector2D::ZeroVector);

	UFUNCTION()
		virtual void FadeOut(const FVector2D& UVPos = FVector2D::ZeroVector);


};
