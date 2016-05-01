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

UENUM(BlueprintType)
enum class EAgentAnimState :uint8 {

	IDLE,
	MOVING_RIGHT,
	MOVING_LEFT,
	MOVING_DOWN,
	MOVING_UP,

};

UENUM(BlueprintType)
enum class EAgentFacingState :uint8 {

	UP,
	DOWN,
	RIGHT,
	LEFT
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

	UPROPERTY(VisibleAnywhere, Category = Agent)
		EAgentAnimState AgentAnimState;

	UPROPERTY(VisibleAnywhere, Category = Agent)
		EAgentFacingState AgentFacingState;

	UPROPERTY(EditDefaultsOnly, Category = "Agent")
		FName Agent_Name;

	UPROPERTY(EditDefaultsOnly,  Category = "Agent")
		EAgentType Agent_Type;

	UPROPERTY(EditDefaultsOnly, Category = "Agent")
		FAgentStats Stats;

	UPROPERTY(EditDefaultsOnly,  Category = "Animation")
	class UPaperFlipbook* IdleDownAnimation;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
		UPaperFlipbook* IdleUpAnimation;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
		UPaperFlipbook* IdleRightAnimation;

	UPROPERTY(EditDefaultsOnly,  Category = "Animation")
		UPaperFlipbook* Move_Right_Animation;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
		UPaperFlipbook* Move_Up_Animation;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
		UPaperFlipbook* Move_Down_Animation;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Location)
		TWeakObjectPtr<class ALocation> Cur_Location;

	UPROPERTY()
		TWeakObjectPtr<class AStatementDatabase> Database_Ref;

	AAgent(const FObjectInitializer& Initializer);

	UFUNCTION(BlueprintPure, Category = Agent)
		EAgentAnimState GetAnimState();

	UFUNCTION(BlueprintPure, Category = Agent)
		EAgentFacingState GetFacingState();

	UFUNCTION(BlueprintCallable, Category = Agent)
		void SetAnimState(EAgentAnimState newState);

	UFUNCTION(BlueprintCallable, Category=  Agent)
		virtual void InitializeAgent();

	UFUNCTION(BlueprintCallable, Category = Agent)
		virtual void UpdateFlipbook();

	UFUNCTION(BlueprintCallable, Category = Agent)
		virtual void MoveRight(float input);

	UFUNCTION(BlueprintCallable, Category = Agent)
		 virtual void MoveUp(float input);


	void BeginPlay() override;




};
