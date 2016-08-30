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
		TAssetPtr<UPractice> PracticeBlueprint;
	

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
		TArray<FStringAssetReference> ActionsRef;
	
	UPractice(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "Practice")
		static UPractice* NewPractice(const FString& newStatementString);

	UFUNCTION(BlueprintPure, Category = "Actions")
		void AddToActionsArray(TArray<UAction*>& InActions);
	
	
};
