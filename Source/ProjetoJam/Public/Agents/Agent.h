// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperCharacter.h"
#include "Agent.generated.h"

UENUM(BlueprintType)
enum class EAgentType : uint8
{
	PLAYER,
	SPECIAL,
	GRUNT,
};

USTRUCT()
struct FAgentStats
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		float Cur_Life;

	UPROPERTY()
		float Max_Life;

	FAgentStats() 
		:Max_Life(100.0f),
		Cur_Life(Max_Life)
	{}


};

class UFaction;

/**
 *
 */
UCLASS()
class PROJETOJAM_API AAgent : public APaperCharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Agent")
		FName Agent_Name;

	UPROPERTY(EditDefaultsOnly,  Category = "Agent")
		EAgentType Agent_Type;

	UPROPERTY(EditDefaultsOnly, Category = "Agent")
		FAgentStats Stats;

	UPROPERTY(EditDefaultsOnly,  Category = "Animation")
	class UPaperFlipbook* Idle_Animation;

	UPROPERTY(EditDefaultsOnly,  Category = "Animation")
		UPaperFlipbook* Move_Right_Animation;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
		UPaperFlipbook* Move_Up_Animation;

	UPROPERTY()
		UFaction* Faction;

	UPROPERTY()
		TArray<class UItem*> Inventory;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Location)
		TWeakObjectPtr<class ALocation> Cur_Location;

	UPROPERTY()
		TWeakObjectPtr<class AStatementDatabase> Database_Ref;

	AAgent(const FObjectInitializer& Initializer);

	UFUNCTION()
		virtual void InitializeAgent();

	UFUNCTION()
		virtual void MoveRight(float input);

	UFUNCTION()
		 virtual void MoveUp(float input);


	void BeginPlay() override;




};
