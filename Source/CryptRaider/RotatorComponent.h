// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RotatorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API URotatorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URotatorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetShouldRotate(bool ShouldRotate);

	UPROPERTY(EditAnywhere)
	float TargetYaw = 0.0f;//Target Yaw rotation for door to reach

	UPROPERTY(EditAnywhere)
	float RotateSpeed = 0.0f;

	UPROPERTY(EditAnywhere)
	bool ShouldRotate = false;

	FRotator StartingRotation;
};
