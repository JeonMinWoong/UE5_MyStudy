// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

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
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* Physicshandle = GetPhysicsHandle();
	if(Physicshandle == nullptr)
	{
		return;
	}

	if(Physicshandle->GetGrabbedComponent() != nullptr)
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		Physicshandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
}

void UGrabber::Garb()
{
	UPhysicsHandleComponent* Physicshandle = GetPhysicsHandle();
	if(Physicshandle == nullptr)
	{
		return;
	}
	
	FHitResult OutHitResult;
	if(GetGrabbableInReach(OutHitResult))
	{
		UPrimitiveComponent* HitComponent = OutHitResult.GetComponent();
		HitComponent->WakeAllRigidBodies();
		Physicshandle->GrabComponentAtLocationWithRotation(
			HitComponent, NAME_None, OutHitResult.ImpactPoint, GetComponentRotation()
		);
	}
}


void UGrabber::Release()
{
	UPhysicsHandleComponent* Physicshandle = GetPhysicsHandle();
	if(Physicshandle == nullptr)
	{
		return;
	}
	
	if(Physicshandle->GetGrabbedComponent() != nullptr)
	{
		Physicshandle->ReleaseComponent();
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("NULL"));
	}
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* Result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(Result == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Grabber NUll"));
	}

	return Result;
}

bool UGrabber::GetGrabbableInReach(FHitResult& OutHitResult) const
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;
	DrawDebugLine(GetWorld(), Start, End, FColor::Red);
	DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Blue, false, 5);
	
	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	return GetWorld()->SweepSingleByChannel(
		OutHitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel2, Sphere);
}

