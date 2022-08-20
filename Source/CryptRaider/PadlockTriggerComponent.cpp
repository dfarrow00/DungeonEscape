// Fill out your copyright notice in the Description page of Project Settings.


#include "PadlockTriggerComponent.h"
#include "Components/AudioComponent.h"

UPadlockTriggerComponent::UPadlockTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPadlockTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UPadlockTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Rotator == nullptr)
	{
		return;
	}

	//If acceptable actor enters trigger, destory the actor, set rotating actor to rotate, and destroy owner actor (padlock).
	AActor* Actor = GetAcceptableActor();
	if (Actor != nullptr)
	{
		Actor->Destroy();
		Rotator->SetShouldRotate(true);
		GetOwner()->Destroy();
	}
}

void UPadlockTriggerComponent::SetRotatorComponent(URotatorComponent* NewRotator)
{
	Rotator = NewRotator;
}

//Returns pointer to acceptable actor in trigger area if one is present.
AActor* UPadlockTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	for (int32 i = 0; i < Actors.Num(); i++)
	{
		if (Actors[i]->ActorHasTag(AcceptableActorTag))
		{
			return Actors[i];
		}
	}
	return nullptr;
}