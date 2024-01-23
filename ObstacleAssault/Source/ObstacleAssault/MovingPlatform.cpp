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

	FString name = GetName();

	UE_LOG(LogTemp, Display, TEXT("BeginPlay : %s"), *name);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float deltaTime){
	if(ShouldPlatformReturn()){
		FVector moveDirection = platformVelocity.GetSafeNormal();
		startLocation = startLocation + moveDirection * movedDistance;
		SetActorLocation(startLocation);
		platformVelocity = -platformVelocity;
	}
	else{
		FVector currentLocation = GetActorLocation();
		currentLocation = currentLocation + platformVelocity * deltaTime;
		SetActorLocation(currentLocation);
	}
}

void AMovingPlatform::RotatePlatform(float deltaTime){
	FRotator currentRotation = GetActorRotation();
	currentRotation = currentRotation + rotationVelocity * deltaTime;
	SetActorRotation(currentRotation);
	// 더하는 방식 
	//AddActorLocalRotation(rotationVelocity * deltaTime);
}

bool AMovingPlatform::ShouldPlatformReturn() const {
	return GetDistanceMoved() > movedDistance;
}

float AMovingPlatform::GetDistanceMoved() const {
	return FVector::Dist(startLocation, GetActorLocation());
}
