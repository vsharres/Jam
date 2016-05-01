// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperCharacter.h"
#include "Agent.generated.h"

#define MIN_DELTA_VEL 0.01f
#define MAX_DELTA_VEL 1.0f
#define NORMAL_ROTATION FRotator(0.0f,0.0f,-90.0f) 
#define INVERTED_ROTATION FRotator(180.0f,0.0f,-90.0f)

#define AGENT_DEFAULT_SPEED 10.0f
#define AGENT_DEFAULT_MAX_HEALTH 100.0f

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

USTRUCT(BlueprintType)
struct FAgentStats
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AgentStats)
		float Cur_Life;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AgentStats)
		float Max_Life;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AgentStats)
		float Speed;

	FAgentStats() 
		:Max_Life(AGENT_DEFAULT_MAX_HEALTH),
		Cur_Life(AGENT_DEFAULT_MAX_HEALTH),
		Speed(AGENT_DEFAULT_SPEED)
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

	UPROPERTY(VisibleAnywhere, Category = "Animation")
		EAgentAnimState AgentAnimState;

	UPROPERTY(VisibleAnywhere, Category = "Animation")
		EAgentFacingState AgentFacingState;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayThumbnail = "true"), Category = "Animation")
	class UPaperFlipbook* IdleDownAnimation;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayThumbnail = "true"), Category = "Animation")
		UPaperFlipbook* IdleUpAnimation;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayThumbnail = "true"), Category = "Animation")
		UPaperFlipbook* IdleRightAnimation;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayThumbnail = "true"), Category = "Animation")
		UPaperFlipbook* Move_Right_Animation;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayThumbnail = "true"), Category = "Animation")
		UPaperFlipbook* Move_Up_Animation;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayThumbnail = "true"), Category = "Animation")
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

	void Tick(float DeltaSeconds) override;




};
