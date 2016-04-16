// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Statement/StatementDatabase.h"
#include "Object.h"
#include "Action.generated.h"

class AAgent;

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class PROJETOJAM_API UAction : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Action")
	AAgent* Caller;

	UPROPERTY(EditDefaultsOnly,Category = "Action")
		FStatement ActionStatementPreset;

	UPROPERTY(EditDefaultsOnly, Category = "Action")
		UBehaviorTree* ActionBT;
	
	UAction();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Execute PostConditions", Keywords = "Exe Post"), Category = "Action")
		void ExecutePostConditions();
	virtual void ExecutePostConditions_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Check PreConditions", Keywords = "Check Pre"), Category = "Action")
		bool CheckPreConditions();
	virtual bool CheckPreConditions_Implementation();

	
	
};
