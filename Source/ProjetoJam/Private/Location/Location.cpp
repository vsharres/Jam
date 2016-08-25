// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoJam.h"
#include "Agents/Agent.h"
#include "Public/Location/Location.h"

DEFINE_LOG_CATEGORY(LocationLog);

// Sets default values
ALocation::ALocation(const FObjectInitializer& Initializer)
	:Super(Initializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	LocationName = "";
	ChildLocations.Empty();

	Trigger = Initializer.CreateDefaultSubobject<USphereComponent>(this, "Trigger");

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ALocation::OnTriggerBeginOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &ALocation::OnTriggerEndOverlap);



}

TArray<ALocation*> ALocation::GetChildLocations()
{
	return ChildLocations;
}

bool ALocation::IsLocationChild(ALocation* LocationToCompare)
{
	if (!LocationToCompare)
	{
		UE_LOG(LocationLog, Warning, TEXT("Can not compare a null pointer location."));
		return false;
	}

	ALocation* tempLocal = LocationToCompare;

	if (ChildLocations.Contains(tempLocal))
	{
		return true;
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

void ALocation::OnTriggerBeginOverlap(class UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AAgent* agent = Cast<AAgent>(OtherActor);

	if (agent->IsValidLowLevelFast())
	{

	}
}

void ALocation::OnTriggerEndOverlap(class UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

