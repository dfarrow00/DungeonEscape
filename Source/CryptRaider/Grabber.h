// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Engine/World.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Release();

	UFUNCTION(BlueprintCallable)
	void Grab();

private:

	UPhysicsHandleComponent* GetPhysicsHandle();

	bool GetGrabbableInReach(FHitResult& OutHitResult) const;
	
	UPROPERTY(EditAnywhere)
	float MaxGrabDist = 400;
		
	UPROPERTY(EditAnywhere)
	float GrabRadius = 100;

	UPROPERTY(EditAnywhere)
	float HoldDistance = 200;

	TArray<AActor*> Visible;//Stores actors overlapping with sphere sweep in previous tick. This allows highlight outline to be removed when no longer overlapping.
	TArray<AActor*> CurrentlyVisible;//Stores actors overlapping with sphere sweep in current frame.
};
