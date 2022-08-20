// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	//If acceptable actor is found, attach it to this component and set the Mover component to move.
	AActor* Actor = GetAcceptableActor();
	if (Actor != nullptr)
	{
		if (Mover != nullptr)
		{
			UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
			if (Component != nullptr)
			{
				Component->SetSimulatePhysics(false);
			}
			Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
			Mover->SetShouldMove(true);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Null Mover"));
		}
	}
	else
	{
		if (Mover != nullptr)
		{
			Mover->SetShouldMove(false);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Null Mover"));
		}
	}
}

//Returns a pointer to an overlapping actor if one is present.
AActor* UTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	for (int32 i = 0; i < Actors.Num(); i++)
	{
		if (Actors[i]->ActorHasTag(AcceptableActorTag) && !Actors[i]->ActorHasTag("Grabbed"))
		{
			return Actors[i];
		}
	}
	return nullptr;
}

void UTriggerComponent::SetMover(UMover* NewMover)
{
	Mover = NewMover;
}