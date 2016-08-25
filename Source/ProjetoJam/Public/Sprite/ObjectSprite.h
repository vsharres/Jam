// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Sprite/FadableSprite.h"
#include "ObjectSprite.generated.h"

UENUM(BlueprintType)
enum class ETileSize : uint8
{
	L1W1,
	L2W1,
	L2W2
};

/**
 * 
 */
UCLASS()
class PROJETOJAM_API AObjectSprite : public AFadableSprite
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditAnywhere, Category = Tile)
		ETileSize TileSize;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collider)
		UBoxComponent* Collider;

public:
		AObjectSprite(const FObjectInitializer& ObjectInitializer);

		UFUNCTION(BlueprintPure, Category = Tile)
			ETileSize GetTileSize();

		UFUNCTION(BlueprintCallable, Category = Tile)
			void SetTileSize(ETileSize newSize);


#if WITH_EDITOR
		void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif


	
	
};
