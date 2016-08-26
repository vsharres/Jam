// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SaveState.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI, Blueprintable, meta = (CannotImplementInterfaceInBlueprint))
class USaveState : public UInterface
{
	GENERATED_UINTERFACE_BODY()
	
	
};

class ISaveState
{
	GENERATED_IINTERFACE_BODY()

		UFUNCTION(BlueprintCallable, Category = "SaveGame")
		virtual void SaveState();

};




