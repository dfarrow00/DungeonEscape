// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "DrawDebugHelpers.h"

UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr)
	{
		return;
	}

	//If an object is being held, set object position to target location.
	if (PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}

	CurrentlyVisible.Empty();

	//Enables all grabbable objects to render custom depth. This renders outline material around the object.
	FHitResult HitResult;
	if (GetGrabbableInReach(HitResult))
	{
		AActor* HitActor = HitResult.GetActor();
		TArray<UStaticMeshComponent*> Components;
		HitActor->GetComponents<UStaticMeshComponent>(Components);

		for (UStaticMeshComponent* Component : Components)
		{
			Component->SetRenderCustomDepth(true);
			CurrentlyVisible.Add(HitActor);
		}
	}

	//All actors that are no longer in the sphere sweep have outline removed.
	for (AActor* Actor : Visible)
	{
		if (CurrentlyVisible.Find(Actor) == INDEX_NONE)
		{
			TArray<UStaticMeshComponent*> ActorComponents;
			Actor->GetComponents(ActorComponents);
			for (UStaticMeshComponent* ActorComponent : ActorComponents)
			{
				ActorComponent->SetRenderCustomDepth(false);
			}
		}
	}
	Visible = CurrentlyVisible;
}

//Called when left click is released. Drops object if one is being held.
void UGrabber::Release()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	UPrimitiveComponent* GrabbedComponent = PhysicsHandle->GetGrabbedComponent();
	if (PhysicsHandle == nullptr || GrabbedComponent == nullptr)
	{
		return;
	}

	GrabbedComponent->WakeAllRigidBodies();//Ensures actor is simulating physics.
	PhysicsHandle->ReleaseComponent();
	GrabbedComponent->GetOwner()->Tags.Remove("Grabbed");
}

//Called when left click is pressed. Picks up object using Physics Handle component.
void UGrabber::Grab()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr)
	{
		return;
	}

	FHitResult HitResult;
	if (GetGrabbableInReach(HitResult))
	{
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->WakeAllRigidBodies();
		PhysicsHandle->GrabComponentAtLocationWithRotation(HitComponent, NAME_None, HitResult.ImpactPoint, GetComponentRotation());

		HitResult.GetActor()->Tags.Add("Grabbed");
	}
}

//Returns the Physics Handle component of the owner actor if it has one.
UPhysicsHandleComponent* UGrabber::GetPhysicsHandle()
{
	UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Physics Handle component not found"));
	}
	return PhysicsHandle;
}

/*Returns a boolean indicating if there are grabbable objects in reach.
  Sets HitResult reference to result of sphere sweep*/
bool UGrabber::GetGrabbableInReach(FHitResult& OutHitResult) const
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDist;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);

	return GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel2, Sphere);
}

