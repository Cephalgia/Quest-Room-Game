// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class QUESTROOM_API UGrabber : public UActorComponent
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

private:
	float Reach = 100.f;
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;
	
	struct PlayerLocationAndRotation
	{
		FVector PlayerLocation;
		FRotator PlayerRotation;
	};
	
	// Ray-cast and grab an object in reach
	void Grab();
	
	// Called on grab release
	void Release();
	
	// Finds attached physics handle
	void FindPhysicsHandleComponent();
	
	// Sets up attached input component
	void SetupInputComponent();
	
	// Returns hit for the first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();
	
	// Returns the end point of line trace
	const FVector GetLineTraceEnd();
	
	// Get player view point
	const PlayerLocationAndRotation GetPlayerLocationAndRotation();
	
};
