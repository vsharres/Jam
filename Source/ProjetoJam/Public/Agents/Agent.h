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
		FName AgentName;

	UPROPERTY()
		float Cur_Life;

	UPROPERTY()
		float Max_Life;

	UPROPERTY()
		EAgentType Agent_Type;

	FAgentStats() 
		:AgentName(""),
		Max_Life(100.0f),
		Cur_Life(Max_Life),
		Agent_Type(EAgentType::GRUNT)
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Animation)
	class UPaperFlipbook* Idle_Animation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Animation)
	UPaperFlipbook* Move_Right_Animation;

	/*UPROPERTY()
		UFaction Faction;*/

	/*UPROPERTY()
		TArray<UItem*> Items;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Location)
		class ALocation* Cur_Location;

	AAgent(const FObjectInitializer& Initializer);







};
