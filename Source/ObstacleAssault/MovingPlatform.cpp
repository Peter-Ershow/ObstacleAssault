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
	RotatePlatform(DeltaTime);
}


void AMovingPlatform::MovePlatform(float DeltaTime)
{
	if (ShouldPlatformReturn())
	{
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		UE_LOG(LogTemp, Display, TEXT("Safe Normal for Platform: %s XYZ are: %ls"), *Name, *MoveDirection.ToString())
		StartLocation = StartLocation + MoveDirection * MoveDistance;
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}
	else
	{
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);
		SetActorLocation(CurrentLocation);
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation = CurrentRotation + RotationVelocity * DeltaTime;
	SetActorRotation(CurrentRotation);
}

bool AMovingPlatform::ShouldPlatformReturn() const
{
	return GetDistanceMoved() > MoveDistance;
}

float AMovingPlatform::GetDistanceMoved() const
{
	return FVector::Dist(StartLocation, GetActorLocation());
}
