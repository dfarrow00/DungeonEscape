// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "RotatorComponent.h"
#include "PadlockTriggerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CRYPTRAIDER_API UPadlockTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()

public: 
	UPadlockTriggerComponent();

protected:
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetRotatorComponent(URotatorComponent* Rotator);

	UPROPERTY(EditAnywhere)
	FName AcceptableActorTag;//Tag that objects should have to be deemed acceptable.

private:
	AActor* GetAcceptableActor() const;

	URotatorComponent* Rotator;//Refernce to the Rotator component of the Owner Actor
};
