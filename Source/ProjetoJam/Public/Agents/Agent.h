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

/**
 *
 */
UCLASS()
class PROJETOJAM_API AAgent : public APaperCharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Agent")
		FName Agent_Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Agent")
		EAgentType Agent_Type;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats")
		FAgentStats Stats;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	class UPaperFlipbook* Idle_Animation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	UPaperFlipbook* Move_Right_Animation;

	

	/*UPROPERTY()
		UFaction Faction;*/

	/*UPROPERTY()
		TArray<UItem*> Items;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Location)
		class ALocation* Cur_Location;

	AAgent(const FObjectInitializer& Initializer);







};
