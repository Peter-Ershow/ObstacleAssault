// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

#include <string>

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
	StartLocation = GetActorLocation();
	
	FString MyString = "Peter";
	
	UE_LOG(LogTemp, Display, TEXT("Hello boys I am: %s"), *MyString);
	UE_LOG(LogTemp, Display, TEXT("But my real name is: %s"), *Name);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// YES YES YES using Ticks, I am just learning...(Part of a lecture)

	MovePlatform(DeltaTime);
}


void AMovingPlatform::MovePlatform(float DeltaTime)
{
	FVector CurrentLocation = GetActorLocation();

	CurrentLocation = CurrentLocation + PlatformVelocity * DeltaTime;

	SetActorLocation(CurrentLocation);

	float DistanceMoved = FVector::Dist(StartLocation, CurrentLocation);

	//reverse direction
	if(DistanceMoved > MovedMaxDistance)
	{
		float OverShoot = DistanceMoved - MovedMaxDistance;
		UE_LOG(LogTemp, Display, TEXT("Platform %s overshot by %f, Distance Moved: %f, MaxDistance: %f"), *Name, OverShoot, DistanceMoved, MovedMaxDistance)

		RotatePlatform();
	}
}

void AMovingPlatform::RotatePlatform()
{
	FVector MoveDirection = PlatformVelocity.GetSafeNormal();
	UE_LOG(LogTemp, Display, TEXT("Safe Normal for Platform: %s XYZ are: %ls"), *Name, *MoveDirection.ToString())
	
	StartLocation = StartLocation + MoveDirection * MovedMaxDistance;
	SetActorLocation(StartLocation);
	PlatformVelocity = -PlatformVelocity;
}
