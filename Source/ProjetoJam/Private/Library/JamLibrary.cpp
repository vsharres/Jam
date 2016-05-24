// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "JamLibrary.h"


AStatementDatabase* UJamLibrary::GetStatementDatabase(UObject* WorldContextObject)
{
	if (WorldContextObject)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject);
		if (World != nullptr)
		{
			for (TActorIterator<AStatementDatabase> ActorItr(World); ActorItr; ++ActorItr)
			{
				if ((*ActorItr)->IsValidLowLevel())
				{
					return *ActorItr;
				}
			}
		}
	}

	return nullptr;
}

bool UJamLibrary::Trace(UWorld* World, AActor* ActorToIgnore, const FVector& Start, const FVector& End, FHitResult& HitOut, ECollisionChannel CollisionChannel /*= ECC_Pawn*/, bool ReturnPhysMat /*= false*/)
{
	if (!World)
	{
		return false;
	}

	FCollisionQueryParams TraceParams(FName(TEXT("Trace")), true, ActorToIgnore);
	TraceParams.bTraceComplex = true;
	//TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = ReturnPhysMat;

	//Ignore Actors
	TraceParams.AddIgnoredActor(ActorToIgnore);

	//Re-initialize hit info
	HitOut = FHitResult(ForceInit);

	//Trace!
	World->LineTraceSingleByChannel(
		HitOut,		//result
		Start,	//start
		End, //end
		CollisionChannel, //collision channel
		TraceParams
		);

	//Hit any Actor?
	return (HitOut.GetActor() != NULL);
}

bool UJamLibrary::TraceSphere(UWorld* World, AActor* ActorToIgnore, const FVector& Start, const FVector& End, const FRotator& Rot, float Radius, TArray<FHitResult>& HitsOut, ECollisionChannel CollisionChannel /*= ECC_Pawn*/, bool ReturnPhysMat /*= false*/)
{
	if (!World)
	{
		return false;
	}
	
	FCollisionQueryParams TraceParams(FName(TEXT("SphereTrace")), true, ActorToIgnore);
	TraceParams.bTraceComplex = true;
	//TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = ReturnPhysMat;

	FCollisionShape TraceShape;
	TraceShape.ShapeType = ECollisionShape::Sphere;
	TraceShape.SetSphere(Radius);

	//Ignore Actors
	TraceParams.AddIgnoredActor(ActorToIgnore);

	HitsOut = TArray<FHitResult>();

	World->SweepMultiByChannel(HitsOut, Start, End, Rot.Quaternion(), CollisionChannel, TraceShape, TraceParams);

	return (HitsOut.Num() > 0);

}
