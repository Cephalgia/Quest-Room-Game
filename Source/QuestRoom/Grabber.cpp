// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestRoom.h"
#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// Find attached physics handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(!PhysicsHandle) 
	{
		UE_LOG(LogTemp, Error, TEXT("%s handle not found"), *(GetOwner()->GetName()));
	}
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get player view point
	FVector PlayerLocation;
	FRotator PlayerRotation;
	GetWorld()-> GetFirstPlayerController()->GetPlayerViewPoint(PlayerLocation, PlayerRotation);
	
	FVector LineTraceEnd = PlayerLocation + PlayerRotation.Vector()*Reach;
	DrawDebugLine(GetWorld(), PlayerLocation, LineTraceEnd, FColor(255, 0, 0), false, 0.f, 0.f, 10.f);
	
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		PlayerLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);
	if(Hit.GetActor() != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is hit"), *(Hit.GetActor()->GetName()));
	}
	
}

