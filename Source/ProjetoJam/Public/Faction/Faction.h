// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Faction.generated.h"

#define MIN_STATUS -10
#define MAX_STATUS 10

UENUM(BlueprintType)
enum class EFactionType :uint8 {

	PLAYER,
	FACTION1,
	FACTION2,
	FACTION3

};

USTRUCT()
struct FFactionStatus
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(VisibleAnywhere,Category = "Faction Status Struct")
		int32 StatusPlayer;

	UPROPERTY(VisibleAnywhere, Category = "Faction Status Struct")
		int32 StatusFaction1;

	UPROPERTY(VisibleAnywhere, Category = "Faction Status Struct")
		int32 StatusFaction2;

	UPROPERTY(VisibleAnywhere, Category = "Faction Status Struct")
		int32 StatusFaction3;

	FFactionStatus()
	{
		StatusPlayer = 0;
		StatusFaction1 = 0;
		StatusFaction2 = 0;
		StatusFaction3 = 0;
	}

	void ClampValues()
	{
		if (StatusPlayer < MIN_STATUS)
		{
			StatusPlayer = -10;
		}
		else if (StatusPlayer > MAX_STATUS)
		{
			StatusPlayer = 10;
		}

		if (StatusFaction1 < MIN_STATUS)
		{
			StatusFaction1 = -10;
		}
		else if (StatusFaction1 > MAX_STATUS)
		{
			StatusFaction1 = 10;
		}

		if (StatusFaction2 < MIN_STATUS)
		{
			StatusFaction2 = -10;
		}
		else if (StatusFaction2 > MAX_STATUS)
		{
			StatusFaction2 = 10;
		}

		if (StatusFaction3 < MIN_STATUS)
		{
			StatusFaction3 = -10;
		}
		else if (StatusFaction3 > MAX_STATUS)
		{
			StatusFaction3 = 10;
		}
	}

};

/**
 * 
 */
UCLASS()
class PROJETOJAM_API UFaction : public UObject
{
	GENERATED_BODY()

private:

	UPROPERTY()
		FFactionStatus Status;

public:

	UPROPERTY()
		EFactionType FactionType;

	UPROPERTY()
		TArray<class UStatement*> BeliefStatements;

	UFaction(const FObjectInitializer& Initializer);

	UFUNCTION(BlueprintPure, Category = "Faction")
		int32 GetStatusToPlayer();

	UFUNCTION(BlueprintPure, Category = "Faction")
		int32 GetStatusToFaction(EFactionType type);

	UFUNCTION(BlueprintCallable, Category = "Faction")
		void InitializeFaction(EFactionType type);
	
	UFUNCTION(BlueprintCallable, Category = "Faction")
		void ChangeRelationTo(EFactionType type, int32 value);
	
};
