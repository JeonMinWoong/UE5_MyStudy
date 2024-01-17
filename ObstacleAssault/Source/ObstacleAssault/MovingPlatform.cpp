// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	startLocation = GetActorLocation();

	UE_LOG(LogTemp, Display, TEXT("movidDistance: %f"), movedDistance);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Move platform forwards
		// Get current location
	FVector currentLocation = GetActorLocation();
		// Add vector to that location
	currentLocation = currentLocation + platformVelocity * DeltaTime;
		// Set the location
	SetActorLocation(currentLocation);
	// Send Platform back if gone too far
		// Check how far we`ve moved
	distValue = FVector::Dist(startLocation, currentLocation);
		// Reverse direction of motion if gone too far
	if(distValue > movedDistance){
		float txetValue = distValue - movedDistance;

		UE_LOG(LogTemp, Display, TEXT("My Txet : %f"), txetValue);

		FVector moveDirection = platformVelocity.GetSafeNormal();
		startLocation = startLocation + moveDirection * movedDistance;
		SetActorLocation(startLocation);
		platformVelocity = -platformVelocity;
	}
}

