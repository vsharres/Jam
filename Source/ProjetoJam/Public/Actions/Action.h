// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Statement.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Action.generated.h"


/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, ABSTRACT)
class PROJETOJAM_API UAction : public UStatement
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Action")
		bool bIsActive;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Controller")
		AAgentController* Caller;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Action")
	class UPractice* ParentPractice;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Action")
		TAssetPtr<UBehaviorTree> ActionBT;
	
	UAction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "Action")
		void InstantiateAction(UPractice* practice, class AAgentController* agentCaller);

	UFUNCTION(BlueprintCallable, Category = "Action")
		void StartAction();

	UFUNCTION(BlueprintCallable, Category = "Action")
		void StopAction();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Init Blackboard", Keywords = "Init BlackBoard"), Category = "Action")
		void InitializeBlackBoard();
	virtual void InitializeBlackBoard_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Exec PostConditions", Keywords = "Exec Post"), Category = "Action")
		void ExecutePostConditions();
	virtual void ExecutePostConditions_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Check PreConditions", Keywords = "Check Pre"), Category = "Action")
		bool CheckPreConditions();
	virtual bool CheckPreConditions_Implementation();
	
};
