// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestRoom.h"
#include "ChargeDevice.h"


// Sets default values for this component's properties
UChargeDevice::UChargeDevice()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UChargeDevice::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	
}


// Called every frame
void UChargeDevice::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(SunTrigger != nullptr)
	{
		if(SunTrigger->IsOverlappingActor(Owner))
		{
			DeviceCharged.Broadcast();
			
			UE_LOG(LogTemp, Warning, TEXT("Event broadcast"));
			
		}
	}
}

