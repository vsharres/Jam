// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "LocationComponent.h"
#include "AgentSpawner.h"

ULocationComponent::ULocationComponent()
{
	SetCollisionProfileName(FName(TEXT("Trigger")));
	ParentSpawner = Cast<AAgentSpawner>(GetOwner());
}

void ULocationComponent::BeginPlay()
{
	Database = UJamLibrary::GetStatementDatabase(this);
	OnComponentBeginOverlap.AddDynamic(this, &ULocationComponent::OnTriggerBeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &ULocationComponent::OnTriggerEndOverlap);
	check(Database)
}

void ULocationComponent::OnTriggerBeginOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AAgent* agent = Cast<AAgent>(OtherActor);

	if (agent && Database)
	{
		FString newLocationStatement = agent->GetAgentName().ToString() + ".location!" + ParentSpawner->GetSpawnerName().ToString();
		Database->InsertIntoDatabaseWithString(newLocationStatement);
		
	}
}

void ULocationComponent::OnTriggerEndOverlap(class UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AAgent* agent = Cast<AAgent>(OtherActor);

	if (agent && Database)
	{
		check(ParentLocation)
		FString newLocationStatement = agent->GetAgentName().ToString() + ".location!" + ParentLocation->GetSpawnerName().ToString();
		Database->InsertIntoDatabaseWithString(newLocationStatement);
	}
}

