// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "FactionManager.h"
#include "Faction.h"
#include "XmlParser.h"

UFactionManager::UFactionManager(const FObjectInitializer& Initializer)
	:Super(Initializer)
{
	Factions.Empty();

}

TArray<UFaction*> UFactionManager::GetFactions()
{
	return Factions;
}

UFaction* UFactionManager::GetFaction(EFactionType type)
{
	return Factions[(int32)type];
}

void UFactionManager::InitializeFactions()
{
	UFaction* newFaction;

	for (int32 index = 0; index < 4; index++)
	{
		switch (index)
		{
		case 0:

			newFaction = NewObject<UFaction>(this, "PlayerFaction");
			newFaction->InitializeFaction(EFactionType::PLAYER);
			Factions.Add(newFaction);
			break;
		case 1:

			newFaction = NewObject<UFaction>(this, "Faction1");
			newFaction->InitializeFaction(EFactionType::FACTION1);
			Factions.Add(newFaction);
			break;
		case 2:
			newFaction = NewObject<UFaction>(this, "Faction2");
			newFaction->InitializeFaction(EFactionType::FACTION2);
			Factions.Add(newFaction);
			break;
		case 3:
			newFaction = NewObject<UFaction>(this, "Faction3");
			newFaction->InitializeFaction(EFactionType::FACTION3);
			Factions.Add(newFaction);
			break;
		default:
			break;
		}
	}
	check(Factions.Num()==4)
}

void UFactionManager::ParseFactionsFile()
{

	const FXmlFile file(FACTIONS_DATABASE_PATH);
	const FXmlNode* rootNode = file.GetRootNode();

	const TArray<FXmlNode*> factionsNodes = rootNode->GetChildrenNodes();

	for (const auto& node : factionsNodes)
	{
		UStructProperty* stringProperty = FindField<UStructProperty>(GetClass(),*(node->GetTag()));
		
		if (stringProperty)
		{
			FString value = *(stringProperty->ContainerPtrToValuePtr<FString>(stringProperty));
			
		}

		UNumericProperty* numericalProperty = FindField<UNumericProperty>(GetClass(), *(node->GetTag()));

		if (numericalProperty)
		{
			numericalProperty->SetNumericPropertyValueFromString(numericalProperty, *node->GetContent());
		}



	}
}

