// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class CRYPTRAIDER_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Movement")
		FVector PlatformVelocity = FVector(0, 150, 0);

	UPROPERTY(EditAnywhere, Category = "Movement")
		float MoveDistance = 100.0;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float MovementDelay = 0.0f;//The time the actor should wait before moving in the opposite direction.

	UPROPERTY(EditAnywhere, Category = "Rotation")
		FRotator RotationVelocity;

	FVector StartLocation;

private:
	void MovePlatform(float DeltaTime);
	void RotatePlatform(float DeltaTime);

	bool ShouldPlatformReturn() const;

	float CurrentTime = 0.0f;
};
