// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "StatementsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJETOJAM_API UStatementsComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly, Category = "Root")
		FString RootName;

	UPROPERTY()
	class UStatementDatabase* Database;

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statements")
		TArray<FString> Statements;

	// Sets default values for this component's properties
	UStatementsComponent(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
		void AddStatementsToDatabase();
		
	
};
