// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoJam.h"
#include "Public/Location/Location.h"

DEFINE_LOG_CATEGORY(LocationLog);

// Sets default values
ALocation::ALocation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LocationName = "";
	ParentLocation = nullptr;

}

void ALocation::SetLocationStament()
{
	FString text = LocationName;

	while (ParentLocation != nullptr)
	{
		text = ParentLocation->LocationName + "." + LocationName;
	}

	text = "World." + text;

	FStatement statement = FStatement(text);
	
}

ALocation* ALocation::GetParentLocation()
{
	return ParentLocation;
}

bool ALocation::IsLocationChild(ALocation* LocationToCompare)
{
	if (!LocationToCompare)
	{
		UE_LOG(LocationLog, Warning, TEXT("Can not compare a null pointer location."));
		return false;
	}

	ALocation* tempLocal = LocationToCompare;

	while (tempLocal)
	{
		if (tempLocal == LocationToCompare->ParentLocation)
		{
			return true;
		}
		else
		{
			tempLocal = tempLocal->ParentLocation;
		}
	}

	return false;
}

// Called when the game starts or when spawned
void ALocation::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALocation::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

