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
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));
	auto GrabResult = GetFirstPhysicsBodyInReach();
    auto ComponentToGrab = GrabResult.GetComponent();
    

    if(GrabResult.GetActor())
    {
        PhysicsHandle->GrabComponent(ComponentToGrab,
                                     NAME_None,
                                     ComponentToGrab->GetOwner()->GetActorLocation(),
                                     true //allow rotation
                                     );
    }

}

void UGrabber::Release() 
{
	UE_LOG(LogTemp, Warning, TEXT("Grab released"));
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
		UE_LOG(LogTemp, Warning, TEXT("%s input component found"), *(GetOwner()->GetName()));
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	// Get player view point
	FVector PlayerLocation;
	FRotator PlayerRotation;
	GetWorld()-> GetFirstPlayerController()->GetPlayerViewPoint(PlayerLocation, PlayerRotation);
	
	FVector LineTraceEnd = PlayerLocation + PlayerRotation.Vector()*Reach;
	
	
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		PlayerLocation,
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
        FVector PlayerLocation;
        FRotator PlayerRotation;
        GetWorld()-> GetFirstPlayerController()->GetPlayerViewPoint(PlayerLocation, PlayerRotation);

        FVector LineTraceEnd = PlayerLocation + PlayerRotation.Vector()*Reach;
        PhysicsHandle->SetTargetLocation(LineTraceEnd);
    }

}

