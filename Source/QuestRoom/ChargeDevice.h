// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "ChargeDevice.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FChargeEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class QUESTROOM_API UChargeDevice : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UChargeDevice();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
	FChargeEvent DeviceCharged;

private:
	UPROPERTY(EditAnywhere)
	ATriggerVolume* SunTrigger = nullptr;	
	AActor* Owner = nullptr;	
	
};
