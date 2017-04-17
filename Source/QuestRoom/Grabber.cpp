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

	FindPhysicsHandleComponent();
	
	SetupInputComponent();
	
	
}

void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(!PhysicsHandle) 
	{
		UE_LOG(LogTemp, Error, TEXT("%s handle not found"), *(GetOwner()->GetName()));
	}
}

void UGrabber::Grab() 
{
	auto GrabResult = GetFirstPhysicsBodyInReach();
    auto ComponentToGrab = GrabResult.GetComponent();
    
	// Attach PhysicsHandle if something's grabbed
    if(GrabResult.GetActor())
    {
        PhysicsHandle->GrabComponent(ComponentToGrab,
                                     NAME_None, // no bones
                                     ComponentToGrab->GetOwner()->GetActorLocation(),
                                     true //allow rotation
                                     );
    }

}

void UGrabber::Release() 
{
	PhysicsHandle->ReleaseComponent();
}

void UGrabber::SetupInputComponent() 
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if(!InputComponent) 
	{
		UE_LOG(LogTemp, Error, TEXT("%s input component not found"), *(GetOwner()->GetName()));
	} else 
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

const UGrabber::PlayerLocationAndRotation UGrabber::GetPlayerLocationAndRotation()
{
	FVector PlayerLocation;
	FRotator PlayerRotation;
	GetWorld()-> GetFirstPlayerController()->GetPlayerViewPoint(PlayerLocation, PlayerRotation);
	
	PlayerLocationAndRotation Result;
	Result.PlayerLocation = PlayerLocation;
	Result.PlayerRotation = PlayerRotation;
	
	return Result;
}

const FVector UGrabber::GetLineTraceEnd()
{
	
	PlayerLocationAndRotation PlayerPosition = GetPlayerLocationAndRotation();
	
	FVector LineTraceEnd = PlayerPosition.PlayerLocation + PlayerPosition.PlayerRotation.Vector()*Reach;
	return LineTraceEnd;
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	
	FVector LineTraceEnd = GetLineTraceEnd();
	PlayerLocationAndRotation PlayerPosition = GetPlayerLocationAndRotation();
	
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		PlayerPosition.PlayerLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	return Hit;
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if(PhysicsHandle->GrabbedComponent)
    {
        FVector LineTraceEnd = GetLineTraceEnd();
        PhysicsHandle->SetTargetLocation(LineTraceEnd);
    }

}

