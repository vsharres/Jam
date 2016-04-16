// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "StatementDatabase.h"
#include "ArchetypeManager.generated.h"

UENUM(BlueprintType)
enum class EArchetype : uint8
{
	ARIES,
	TAURUS,
	GEMINI,
	CANCER,
	LEO,
	VIRGO,
	LIBRA,
	SCORPIO,
	SAGITARIUS,
	CAPRICORN,
	AQUARIUS,
	PISCES
};

UENUM(BlueprintType)
enum class ERegentType : uint8 {

	SUN,
	MOON,
	MERCURY,
	VENUS,
	MARS,
	JUPITER,
	SATURN,
	URANUS,
	NEPTUNE

};

UENUM(BlueprintType)
enum class EArchetypePositionType : uint8
{
	FIRST,
	SECOND,
	THIRD,
	FOURTH,
	FIFTH,
	SIXTH,
	SEVENTH,
	EIGHT,
	NINGHT,
	TENTH,
	ELEVENTH,
	TWELVETH

};

UENUM(BlueprintType)
enum class EAspectType :uint8
{
	CONJUCTION,
	TRINE,
	SQUARE,
	OPPOSITION
};




USTRUCT(BlueprintType)
struct FArchetype
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY()
		EArchetypePositionType PositionType;

	UPROPERTY()
		EArchetype Type;

	FArchetype()
	{
		PositionType = EArchetypePositionType::FIRST;
		Type = EArchetype::ARIES;

	}

	FArchetype(EArchetypePositionType position, EArchetype type)
	{
		PositionType = position;
		Type = type;
	}

	void AddAchetypeClassStatements(TArray<FStatement>& StatementArray)
	{
		switch (Type)
		{
		case EArchetype::ARIES:
			break;
		case EArchetype::TAURUS:
			break;
		case EArchetype::GEMINI:
			break;
		case EArchetype::CANCER:
			break;
		case EArchetype::LEO:
			break;
		case EArchetype::VIRGO:
			break;
		case EArchetype::LIBRA:
			break;
		case EArchetype::SCORPIO:
			break;
		case EArchetype::SAGITARIUS:
			break;
		case EArchetype::CAPRICORN:
			break;
		case EArchetype::AQUARIUS:
			break;
		case EArchetype::PISCES:
			break;
		default:
			break;
		}
	}

};


USTRUCT(BlueprintType)
struct FArchetypeRegent
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY()
		ERegentType Type;

	UPROPERTY()
		FArchetype Archetype;
		

	FArchetypeRegent()
	{
		Type = ERegentType::SUN;
		Archetype = FArchetype();
		
	}

};

USTRUCT(BlueprintType)
struct FAspect
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY()
		EAspectType Type;

	UPROPERTY()
		FArchetypeRegent AspectTo;

	FAspect()
	{
		Type = EAspectType::CONJUCTION;
		AspectTo = FArchetypeRegent();
	}

};

/**
 *
 */
UCLASS(BlueprintType)
class PROJETOJAM_API UArchetypeManager : public UObject
{
	GENERATED_BODY()


public:

	UPROPERTY()
		FArchetype Archetype;

	UPROPERTY()
		TArray<FArchetypeRegent> Regents;

	TMultiMap<FArchetypeRegent, FAspect> Aspects;

	UArchetypeManager();


	FORCEINLINE static bool ConstPredicate(const FArchetypeRegent& key1, const FArchetypeRegent& key2)
	{
		return (key1.Type < key2.Type);
	}

};
