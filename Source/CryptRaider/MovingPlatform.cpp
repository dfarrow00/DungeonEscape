// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

//Moves the platform using the values of the UProperty variables
void AMovingPlatform::MovePlatform(float DeltaTime)
{
	if (ShouldPlatformReturn() && CurrentTime >= MovementDelay)//If platform should return and movement delay has been reached, reset start location and reverse velocity.
	{
		CurrentTime = 0.0f;
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * MoveDistance;
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}
	else if (ShouldPlatformReturn() && CurrentTime < MovementDelay)//If platform should return but movement delay has not been reached, do not change direction.
	{
		CurrentTime += DeltaTime;
		return;
	}
	else
	{
		FVector currentLocation = GetActorLocation();
		currentLocation += (PlatformVelocity * DeltaTime);
		SetActorLocation(currentLocation);
	}
}

//Rotates platform using RotationVelocity.
void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}

//Returns if the actor has reached its destination and should change direction.
bool AMovingPlatform::ShouldPlatformReturn() const
{
	float distanceMoved = FVector::Dist(StartLocation, GetActorLocation());
	return distanceMoved >= MoveDistance;
}