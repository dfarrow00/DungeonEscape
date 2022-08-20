// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"
#include "Components/AudioComponent.h"

// Sets default values for this component's properties
UMover::UMover()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	StartingLocation = GetOwner()->GetActorLocation();
	TargetLocation = StartingLocation + MoveOffset;
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UAudioComponent* Sound = GetOwner()->FindComponentByClass<UAudioComponent>();

	if (ShouldMove)
	{
		if (!Sound->IsPlaying())
		{
			Sound->Play();
		}

		FVector CurrentLocation = GetOwner()->GetActorLocation();
		float Speed = FVector::Distance(StartingLocation, TargetLocation) / MoveTime;//Speed = Distance / Time

		//Actors position is interpolated to target location using calculated speed.
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
		GetOwner()->SetActorLocation(NewLocation);

		if (NewLocation.Z == TargetLocation.Z)//If target location reached, stop moving
		{
			ShouldMove = false;
		}
	}
	else
	{
		if (Sound->IsPlaying())
		{
			Sound->Stop();
		}
	}
}

void UMover::SetShouldMove(bool NewShouldMove)
{
	if (GetOwner()->GetActorLocation().Z == TargetLocation.Z)
	{
		ShouldMove = false;
		return;
	}
	ShouldMove = NewShouldMove;
}

