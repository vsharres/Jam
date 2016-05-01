// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "ArchetypeManager.h"


UArchetypeManager::UArchetypeManager()
{
	Regents.Empty();
	ResultingStatements.Empty();
	Aspects.Empty();
	Seed = 0;
	Stream = FRandomStream(Seed);
}


void UArchetypeManager::GenerateArchetypes()
{
	Stream.Initialize(Seed);

	Ascendent = FArchetypeRegent(ERegentType::ASCENDENT,(EArchetype)Stream.RandRange(0, 11));

	for (uint8 i = 0; i < 3; i++)
	{
		FArchetypeRegent* newRegent;
		newRegent = FArchetypeRegent::GenerateRegent((ERegentType)i);
		Regents.Add(*newRegent);
	}


}

void UArchetypeManager::GenerateAspects()
{
	for (int32 i = 0; i < Regents.Num() - 1; i++)
	{
		for (int32 j = i + 1; j < Regents.Num(); j++)
		{

			if (Regents[i].InConjunction(Regents[j]))
			{
				FAspect aspect = FAspect(EAspectType::CONJUCTION, Regents[j]);
				FAspect aspectOp = FAspect(EAspectType::CONJUCTION, Regents[i]);

				Aspects.Add((uint8)Regents[i].RegentType, aspect);
				Aspects.Add((uint8)Regents[j].RegentType, aspectOp);

				Aspects.KeySort(ConstPredicate);
			}
			else if (Regents[i].InTrine(Regents[j]))
			{
				FAspect aspect = FAspect(EAspectType::TRINE, Regents[j]);
				FAspect aspectOp = FAspect(EAspectType::TRINE, Regents[i]);

				Aspects.Add((uint8)Regents[i].RegentType, aspect);
				Aspects.Add((uint8)Regents[j].RegentType, aspectOp);

				Aspects.KeySort(ConstPredicate);
			}
			else if (Regents[i].InSquare(Regents[j]))
			{
				FAspect aspect = FAspect(EAspectType::SQUARE, Regents[j]);
				FAspect aspectOp = FAspect(EAspectType::SQUARE, Regents[i]);

				Aspects.Add((uint8)Regents[i].RegentType, aspect);
				Aspects.Add((uint8)Regents[j].RegentType, aspectOp);

				Aspects.KeySort(ConstPredicate);
			}
			else if (Regents[i].InOpposition(Regents[j]))
			{
				FAspect aspect = FAspect(EAspectType::OPPOSITION, Regents[j]);
				FAspect aspectOp = FAspect(EAspectType::OPPOSITION, Regents[i]);

				Aspects.Add((uint8)Regents[i].RegentType, aspect);
				Aspects.Add((uint8)Regents[j].RegentType, aspectOp);

				Aspects.KeySort(ConstPredicate);
			}

		}

	}

}

void UArchetypeManager::CalculateValueOfArchetypes()
{
	TArray<uint8> values;





}

void UArchetypeManager::PopulateStatements()
{

}
