// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperCharacter.h"
#include "Interfaces/Damage.h"
#include "Agent.generated.h"

#define MIN_DELTA_VEL 0.005f


#define AGENT_DEFAULT_SPEED 10.0f
#define AGENT_DEFAULT_MAX_HEALTH 100.0f

#define MIN_E_ANGLE 292.5f
#define MAX_E_ANGLE 327.5f
#define MIN_NE_ANGLE 247.5f
#define MAX_NE_ANGLE 292.5f
#define MIN_N_ANGLE 202.5f
#define MAX_N_ANGLE 247.5f
#define MIN_NW_ANGLE 157.5f
#define MAX_NW_ANGLE 202.5f
#define MIN_W_ANGLE 112.5f
#define MAX_W_ANGLE 157.5f
#define MIN_SW_ANGLE 67.5f
#define MAX_SW_ANGLE 112.5f
#define MIN_S_ANGLE 22.5f
#define MAX_S_ANGLE 67.5f
#define MIN_SE_ANGLE 22.5f
#define MAX_SE_ANGLE 337.5F


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
	MOVING_N,
	MOVING_NW,
	MOVING_W,
	MOVING_SW,
	MOVING_S,
	MOVING_SE,
	MOVING_E,
	MOVING_NE

};

UENUM(BlueprintType)
enum class EAgentFacingState :uint8 {

	N,
	NW,
	W,
	SW,
	S,
	SE,
	E,
	NE
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

class UFaction;

/**
 *
 */
UCLASS()
class PROJETOJAM_API AAgent : public APaperCharacter, public IDamage
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Agent")
		FName Agent_Name;

	UPROPERTY(EditDefaultsOnly,  Category = "Agent")
		EAgentType Agent_Type;

	UPROPERTY(EditAnywhere, Category = "Agent")
		FAgentStats Stats;

	UPROPERTY(VisibleAnywhere, Category = "Animation")
		EAgentAnimState AgentAnimState;

	UPROPERTY(VisibleAnywhere, Category = "Animation")
		EAgentFacingState AgentFacingState;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayThumbnail = "true"), Category = "Animation")
	class UPaperFlipbook* IdleNAnimation;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayThumbnail = "true"), Category = "Animation")
		UPaperFlipbook* IdleNWAnimation;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayThumbnail = "true"), Category = "Animation")
		UPaperFlipbook* IdleWAnimation;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayThumbnail = "true"), Category = "Animation")
		UPaperFlipbook* IdleSWAnimation;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayThumbnail = "true"), Category = "Animation")
		UPaperFlipbook* IdleSAnimation;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayThumbnail = "true"), Category = "Animation")
		UPaperFlipbook* IdleSEAnimation;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayThumbnail = "true"), Category = "Animation")
		UPaperFlipbook* IdleEAnimation;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayThumbnail = "true"), Category = "Animation")
		UPaperFlipbook* IdleNEAnimation;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayThumbnail = "true"), Category = "Animation")
		UPaperFlipbook* MoveNAnimation;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayThumbnail = "true"), Category = "Animation")
		UPaperFlipbook* MoveNWAnimation;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayThumbnail = "true"), Category = "Animation")
		UPaperFlipbook* MoveWAnimation;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayThumbnail = "true"), Category = "Animation")
		UPaperFlipbook* MoveSWAnimation;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayThumbnail = "true"), Category = "Animation")
		UPaperFlipbook* MoveSAnimation;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayThumbnail = "true"), Category = "Animation")
		UPaperFlipbook* MoveSEAnimation;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayThumbnail = "true"), Category = "Animation")
		UPaperFlipbook* MoveEAnimation;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayThumbnail = "true"), Category = "Animation")
		UPaperFlipbook* MoveNEAnimation;

	UPROPERTY(VisibleAnywhere, Category = "Animation")
		UPaperFlipbookComponent* ShadowFlipbook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Location)
		TWeakObjectPtr<class ALocation> Cur_Location;

public:

	UPROPERTY()
		TWeakObjectPtr<class AStatementDatabase> Database_Ref;

	AAgent(const FObjectInitializer& Initializer);

	UFUNCTION(BlueprintPure, Category = Location)
		ALocation* GetLocation();

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

	void OnDamaged(float Damage) override;

	UFUNCTION(BlueprintCallable, Category = Agent)
		virtual void Kill();

};
