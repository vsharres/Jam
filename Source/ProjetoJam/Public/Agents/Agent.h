// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperCharacter.h"
#include "Damage.h"
#include "SaveState.h"
#include "Agent.generated.h"

#define MIN_DELTA_VEL 0.005f

#define AGENT_DEFAULT_SPEED 0.5f
#define AGENT_DEFAULT_MAX_HEALTH 100.0f

#define MIN_RIGHT_ANGLE 295.0f
#define MAX_RIGHT_ANGLE  75.0f
#define MIN_UP_ANGLE 255.0f
#define MAX_UP_ANGLE 295.0f
#define MIN_LEFT_ANGLE 105.0f
#define MAX_LEFT_ANGLE 255.0f
#define MIN_DOWN_ANGLE 75.0f
#define MAX_DOWN_ANGLE 105.0f


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
	MOVING_UP,
	MOVING_LEFT,
	MOVING_DOWN,
	MOVING_RIGHT

};

UENUM(BlueprintType)
enum class EAgentFacingState :uint8 {

	UP,
	LEFT,
	DOWN,
	RIGHT
};

USTRUCT(BlueprintType)
struct FAgentStats
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AgentStats")
		float Cur_Life;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AgentStats")
		float Max_Life;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AgentStats")
		float Speed;

	FAgentStats() 
		:Max_Life(AGENT_DEFAULT_MAX_HEALTH),
		Cur_Life(AGENT_DEFAULT_MAX_HEALTH),
		Speed(AGENT_DEFAULT_SPEED)
	{}

	FAgentStats(float maxLife, float speed)
	{
		Max_Life = maxLife;
		Cur_Life = Max_Life;
		Speed = speed;
	}

	FAgentStats(const FAgentStats& otherStats)
	{
		this->Max_Life = otherStats.Max_Life;
		this->Cur_Life = otherStats.Cur_Life;
		this->Speed = otherStats.Speed;
	}


};



/**
 *
 */
UCLASS()
class PROJETOJAM_API AAgent : public APaperCharacter, public IDamage, public ISaveState
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Agent")
		FName AgentName;

	UPROPERTY(EditDefaultsOnly,  Category = "Agent")
		EAgentType Agent_Type;

	UPROPERTY(EditAnywhere, Category = "Agent")
		FAgentStats Stats;

	UPROPERTY(VisibleAnywhere, Category = "Animation")
		EAgentAnimState AgentAnimState;

	UPROPERTY(VisibleAnywhere, Category = "Animation")
		EAgentFacingState AgentFacingState;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayThumbnail = "true"), Category = "Animation")
	class UPaperFlipbook* IdleUpAnimation;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayThumbnail = "true"), Category = "Animation")
		UPaperFlipbook* IdleLeftAnimation;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayThumbnail = "true"), Category = "Animation")
		UPaperFlipbook* IdleDownAnimation;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayThumbnail = "true"), Category = "Animation")
		UPaperFlipbook* IdleRightAnimation;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayThumbnail = "true"), Category = "Animation")
		UPaperFlipbook* MoveUpAnimation;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayThumbnail = "true"), Category = "Animation")
		UPaperFlipbook* MoveLeftAnimation;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayThumbnail = "true"), Category = "Animation")
		UPaperFlipbook* MoveDownAnimation;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayThumbnail = "true"), Category = "Animation")
		UPaperFlipbook* MoveRightAnimation;

	UPROPERTY(VisibleAnywhere, Category = "Animation")
		UPaperFlipbookComponent* ShadowFlipbook;

	UPROPERTY(VisibleAnywhere, Category = "Statements")
	class UStatementsComponent* StatementsComponent;

public:
	AAgent(const FObjectInitializer& Initializer);

	UFUNCTION(BlueprintPure, Category = "Agent")
		FName GetAgentName();

	UFUNCTION(BlueprintPure, Category = "Agent")
		EAgentAnimState GetAnimState();

	UFUNCTION(BlueprintPure, Category = "Agent")
		EAgentFacingState GetFacingState();

	UFUNCTION(BlueprintCallable, Category = "Agent")
		void SetFacingState(EAgentFacingState newState);

	UFUNCTION(BlueprintCallable, Category = "Animation")
		void SetAnimState(EAgentAnimState newState);

	UFUNCTION(BlueprintCallable, Category = "Animation")
		virtual void UpdateFlipbook();

	UFUNCTION(BlueprintCallable, Category = "Movement")
		virtual void MoveRight(float input);

	UFUNCTION(BlueprintCallable, Category = "Movement")
		 virtual void MoveUp(float input);

	void Tick(float DeltaSeconds) override;

	void OnDamaged(float Damage) override;

	void PostInitializeComponents() override;

	void SaveState() override;
		
	UFUNCTION(BlueprintCallable, Category = Agent)
		void AssignProperties();

	UFUNCTION(BlueprintCallable, Category = Agent)
		virtual void Kill();

};

USTRUCT(BlueprintType)
struct FAgentData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Agent")
		float Max_Life;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Agent")
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Agent")
		FString StatementsFilePath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Agent")
		TSubclassOf<AAgent> AgentBlueprint;

	FAgentData()
		: Max_Life(AGENT_DEFAULT_MAX_HEALTH)
		, Speed(AGENT_DEFAULT_SPEED)
		, StatementsFilePath("")
	{}

};
