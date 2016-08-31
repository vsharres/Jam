// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Statement.h"
#include "Practice.generated.h"

USTRUCT(BlueprintType)
struct FPracticeTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Practice Table")
		TSubclassOf<UPractice> PracticeBlueprintAsset;
	

	FPracticeTable()
	{}

};

/**
 * 
 */
UCLASS(Blueprintable, Blueprintable, ABSTRACT)
class PROJETOJAM_API UPractice : public UStatement
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
		TArray<TSubclassOf<UAction>> ActionsRef;
	
	UPractice(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "Practice")
		static UPractice* NewPractice(UObject* WorldContextObject, const FString& newStatementString, TSubclassOf<UPractice> practiceAsset);

	UFUNCTION(BlueprintPure, Category = "Actions")
		void AddToActionsArray(TArray<UAction*>& InActions, class AAgentController* agentCaller);
	
	
};
