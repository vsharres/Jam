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
	MERCURY,
	VENUS,
	MOON,
	MARS,
	JUPITER,
	SATURN,
	URANUS,
	NEPTUNE,
	PLUTO

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

	bool operator==(const FArchetype& C1)
	{
		if (this->Type == C1.Type && this->PositionType == C1.PositionType)
		{
			return true;
		}

		return false;
	}

	bool operator==(const FArchetype& C1) const
	{
		if (this->Type == C1.Type && this->PositionType == C1.PositionType)
		{
			return true;
		}

		return false;
	}

};


USTRUCT(BlueprintType)
struct FArchetypeRegent
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY()
		ERegentType RegentType;

	UPROPERTY()
		FArchetype Archetype;
		

	FArchetypeRegent()
	{
		RegentType = ERegentType::SUN;
		Archetype = FArchetype();
		
	}

	static FArchetypeRegent* GenerateRegent(ERegentType TypeToGenerate, FArchetype BaseArchetype)
	{
		FArchetypeRegent* generated = new FArchetypeRegent();
		FRandomStream stream;

		if (TypeToGenerate == ERegentType::SUN || TypeToGenerate >= ERegentType::MOON)
		{			

			generated->RegentType = (ERegentType)stream.RandRange(0, 11);
		}
		else
		{
			generated->RegentType = (ERegentType)stream.RandRange(((int32)generated->RegentType) - 1, ((int32)generated->RegentType) + 1);
		}

		generated->Archetype.Type = (EArchetype)((int32)BaseArchetype.Type % (11 + (int32)generated->RegentType));

		return generated;
		
	}

	bool operator==(const FArchetypeRegent& c2)
	{
		if (this->RegentType == c2.RegentType && this->Archetype == c2.Archetype)
		{
			return true;
		}

		return false;
	}

	bool operator==(const FArchetypeRegent& c2) const
	{
		if (this->RegentType == c2.RegentType && this->Archetype == c2.Archetype)
		{
			return true;
		}

		return false;
	}

	bool InConjunction(const FArchetypeRegent& Other) const
	{
		if (*this == Other)
		{
			return false;
		}

		if (this->Archetype.PositionType == Other.Archetype.PositionType)
		{
			return true;
		}
		
		return false;

	}

	bool InTrine(const FArchetypeRegent& Other) const
	{
		if (*this == Other)
		{
			return false;
		}

		const uint8 pos1 = ((uint8)this->Archetype.PositionType + 4) % 11;
		const uint8 pos2 = ((uint8)this->Archetype.PositionType - 4) % 11;

		if (pos1 == (uint8)Other.Archetype.PositionType || pos2 == (uint8)Other.Archetype.PositionType)
		{
			return true;
		}

		return false;
	}

	bool InSquare(const FArchetypeRegent& Other) const 
	{

		if (*this == Other)
		{
			return false;
		}

		const uint8 pos1 = ((uint8)this->Archetype.PositionType + 3) % 11;
		const uint8 pos2 = ((uint8)this->Archetype.PositionType - 3) % 11;

		if (pos1 == (uint8)Other.Archetype.PositionType || pos2 == (uint8)Other.Archetype.PositionType)
		{
			return true;
		}

		return false;

	}

	bool InOpposition(const FArchetypeRegent& Other) const
	{

		if (*this == Other)
		{
			return false;
		}

		const uint8 pos = ((uint8)this->Archetype.PositionType + 6) % 11;

		if (pos == (uint8)Other.Archetype.PositionType)
		{
			return true;
		}

		return false;
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

	FAspect(EAspectType type, FArchetypeRegent aspectTo)
	{
		Type = type;
		AspectTo = aspectTo;
	}

};

USTRUCT(BlueprintType)
struct FArchetypeStatements : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FArchetypeStatements()
		: Type(EArchetype::ARIES),
		Statements("")
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Archetype)
		EArchetype Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Archetype)
		FString Statements;


};


USTRUCT(BlueprintType)
struct FArchetypeRegentStatements : public  FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FArchetypeRegentStatements()
		: Type(ERegentType::SUN),
		Statements("")
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ArchetypeRegent)
		ERegentType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ArchetypeRegent)
		FString Statements;

};

USTRUCT(BlueprintType)
struct FAspectStatements : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FAspectStatements()
		: Type(EAspectType::CONJUCTION),
		Statements("")
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AsoectStatements)
		EAspectType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AsoectStatements)
		FString Statements;


};

USTRUCT(BlueprintType)
struct FAspectTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FAspectTable()
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AspectTable)
		TAssetPtr<UDataTable> Table;

};



/**
 *
 */
UCLASS(BlueprintType)
class PROJETOJAM_API UArchetypeManager : public UObject
{
	GENERATED_BODY()
private:
	UPROPERTY()
		FRandomStream Stream;

public:

	UPROPERTY()
		FArchetype Ascendent;

	UPROPERTY()
		TArray<FArchetypeRegent> Regents;

	UPROPERTY()
		int32 Seed;

	UPROPERTY()
		TArray<FStatement> ResultingStatements;

	TMultiMap<uint8, FAspect> Aspects;


	UArchetypeManager();


	UFUNCTION()
		void GenerateArchetype();

	UFUNCTION()
		void GenerateAspects();

	UFUNCTION()
		virtual void PopulateStatements();


	FORCEINLINE static bool ConstPredicate(const uint8& key1, const uint8& key2)
	{
		return (key1 < key2);
	}

};
