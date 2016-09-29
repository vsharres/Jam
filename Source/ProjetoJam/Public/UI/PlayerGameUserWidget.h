// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "PlayerGameUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJETOJAM_API UPlayerGameUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
		APlayerAgent* PlayerRef;


	
	
};
