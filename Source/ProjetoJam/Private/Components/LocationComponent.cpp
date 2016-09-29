// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "LocationComponent.h"
#include "AgentSpawner.h"

ULocationComponent::ULocationComponent(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	SetCollisionProfileName(FName(TEXT("Trigger")));
}

void ULocationComponent::BeginPlay()
{
	Database = UJamLibrary::GetStatementDatabase(this);
	OnComponentBeginOverlap.AddDynamic(this, &ULocationComponent::OnTriggerBeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &ULocationComponent::OnTriggerEndOverlap);

	check(Database)
}

void ULocationComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (OnComponentBeginOverlap.IsAlreadyBound(this, &ULocationComponent::OnTriggerBeginOverlap))
	{
		OnComponentBeginOverlap.RemoveDynamic(this, &ULocationComponent::OnTriggerBeginOverlap);
	}

	if (OnComponentEndOverlap.IsAlreadyBound(this, &ULocationComponent::OnTriggerEndOverlap))
	{
		OnComponentEndOverlap.RemoveDynamic(this, &ULocationComponent::OnTriggerEndOverlap);
	}

	Super::EndPlay(EndPlayReason);
}

void ULocationComponent::OnTriggerBeginOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AAgent* agent = Cast<AAgent>(OtherActor);

	check(Database)

	if (agent && ParentLocation)
	{
		FString newLocationStatement = agent->GetAgentName().ToString() + TEXT(".location!") + ParentLocation->GetSpawnerName().ToString();
		Database->InsertIntoDatabaseWithString(newLocationStatement);
		
	}
}

void ULocationComponent::OnTriggerEndOverlap(class UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AAgent* agent = Cast<AAgent>(OtherActor);

	check(Database)

	if (agent && ParentLocation)
	{
		FString newLocationStatement = agent->GetAgentName().ToString() + TEXT(".location!") + ParentLocation->GetSpawnerName().ToString();
		Database->InsertIntoDatabaseWithString(newLocationStatement);
	}
}

