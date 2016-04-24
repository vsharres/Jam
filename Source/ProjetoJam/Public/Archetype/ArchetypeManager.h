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
	

	ASCENDENT,
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
		uint8 Intensity;

	UPROPERTY()
		EArchetype Type;

	FArchetype()
	{
		Intensity=0;
		Type = EArchetype::ARIES;

	}

	FArchetype(EArchetype type)
	{
		Intensity = 0;
		Type = type;
	}
	

	bool operator==(const FArchetype& C1)
	{
		if (this->Type == C1.Type && this->Intensity == C1.Intensity)
		{
			return true;
		}

		return false;
	}

	bool operator==(const FArchetype& C1) const
	{
		if (this->Type == C1.Type && this->Intensity == C1.Intensity)
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

	FArchetypeRegent(ERegentType regent, FArchetype type)
	{
		RegentType = regent;
		Archetype = type;
	}

	static FArchetypeRegent* GenerateRegent(ERegentType TypeToGenerate, FArchetype BaseArchetype)
	{
		FArchetypeRegent* generated = new FArchetypeRegent();
		FRandomStream stream;

		if (TypeToGenerate == ERegentType::SUN || TypeToGenerate >= ERegentType::MOON)	
		{			
			generated->Archetype.Type = (EArchetype)((int32)BaseArchetype.Type % (11 + stream.RandRange(0, 11)));
			
		}
		else
		{
			generated->Archetype.Type = (EArchetype)((int32)BaseArchetype.Type % (11 + stream.RandRange(((int32)TypeToGenerate) - 1, ((int32)TypeToGenerate) + 1)));
		}

		generated->RegentType = TypeToGenerate;
		

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

		if (this->Archetype == Other.Archetype)
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

		const uint8 pos1 = ((uint8)this->Archetype.Type + 4) % 11;
		const uint8 pos2 = ((uint8)this->Archetype.Type - 4) % 11;

		if (pos1 == (uint8)Other.Archetype.Type || pos2 == (uint8)Other.Archetype.Type)
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

		const uint8 pos1 = ((uint8)this->Archetype.Type + 3) % 11;
		const uint8 pos2 = ((uint8)this->Archetype.Type - 3) % 11;

		if (pos1 == (uint8)Other.Archetype.Type || pos2 == (uint8)Other.Archetype.Type)
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

		const uint8 pos = ((uint8)this->Archetype.Type + 6) % 11;

		if (pos == (uint8)Other.Archetype.Type)
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
		: Ascendent(""),
		Sun(""),
		Mercury(""),
		Venus(""),
		Moon(""),
		Mars(""),
		Jupiter(""),
		Saturn(""),
		Uranus(""),
		Neptune(""),
		Pluto("")

	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Archetype)
		FString Ascendent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Archetype)
		FString Sun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Archetype)
		FString Mercury;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Archetype)
		FString Venus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Archetype)
		FString Moon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Archetype)
		FString Mars;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Archetype)
		FString Jupiter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Archetype)
		FString Saturn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Archetype)
		FString Uranus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Archetype)
		FString Neptune;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Archetype)
		FString Pluto;

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
		FArchetypeRegent Ascendent;

	UPROPERTY()
		TArray<FArchetypeRegent> Regents;

	UPROPERTY()
		int32 Seed;

	UPROPERTY()
		TArray<FStatement> ResultingStatements;

	TMultiMap<uint8, FAspect> Aspects;


	UArchetypeManager();


	UFUNCTION()
		void GenerateArchetypes();

	UFUNCTION()
		void GenerateAspects();

	UFUNCTION()
		void CalculateValueOfArchetypes();

	UFUNCTION()
		virtual void PopulateStatements();


	FORCEINLINE static bool ConstPredicate(const uint8& key1, const uint8& key2)
	{
		return (key1 < key2);
	}

};
