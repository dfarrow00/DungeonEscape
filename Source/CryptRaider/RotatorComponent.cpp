// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatorComponent.h"
#include "Components/AudioComponent.h"

// Sets default values for this component's properties
URotatorComponent::URotatorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void URotatorComponent::BeginPlay()
{
	Super::BeginPlay();

	StartingRotation = GetOwner()->GetActorRotation();
}


// Called every frame
void URotatorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ShouldRotate)
	{
		UAudioComponent* Sound = GetOwner()->FindComponentByClass<UAudioComponent>();
		if (!Sound->IsPlaying())
		{
			Sound->Play();
		}

		float CurrentRotation = GetOwner()->GetActorRotation().Yaw;

		if (CurrentRotation == TargetYaw)
		{
			ShouldRotate = false;
		}

		//Doors rotation is interpolated to target rotation. Speed is dictated by user inputted roation speed.
		FRotator OpenDoor(0.0f, TargetYaw, 0.0f);
		OpenDoor.Yaw = FMath::FInterpConstantTo(CurrentRotation, TargetYaw, DeltaTime, RotateSpeed);
		GetOwner()->SetActorRotation(OpenDoor);
	}
	else
	{
		UAudioComponent* Sound = GetOwner()->FindComponentByClass<UAudioComponent>();
		if (Sound->IsPlaying())
		{
			Sound->Stop();
		}
	}
}

void URotatorComponent::SetShouldRotate(bool NewShouldRotate)
{
	ShouldRotate = NewShouldRotate;
}

