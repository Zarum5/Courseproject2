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

	StartLocation = GetActorLocation();
	StartRotation = GetActorRotation();
	NameString = GetName();
	if (EndLocationIsRelative) {
		EndLocation = StartLocation + EndLocation;
	}

	//type "ulog" to create!
	//UE_LOG(LogTemp, Display, TEXT("Configured Moved Distance: %f"), MoveDistance);

}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);

	RotatePlatform(DeltaTime);
};




//Functions
void AMovingPlatform::MovePlatform(float DeltaTime)
{
	if (ShouldPlatformReturn()) {
		FVector TempStart = StartLocation;
		StartLocation = EndLocation;
		EndLocation = TempStart;
		SetActorLocation(StartLocation);
	}
	else {
	FVector CurrentLocation = GetActorLocation();
	CurrentLocation = CurrentLocation + ((EndLocation-StartLocation).GetSafeNormal() * PlatformVelocity * DeltaTime);
	SetActorLocation(CurrentLocation);
	}
};


void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	if (ShouldPlatformReturnRotate() & (MaxRotationBeforeFlip!=0)) {
		RotationVelocity = RotationVelocity*-1;
		RotationAmount=0;
	}
	AddActorLocalRotation(RotationVelocity*DeltaTime);
	RotationAmount = RotationAmount + abs((RotationVelocity.Yaw+RotationVelocity.Pitch+RotationVelocity.Roll)*DeltaTime);
};




//Pure Functions
bool AMovingPlatform::ShouldPlatformReturn() const
{
	return GetDistanceMoved() > FVector::Dist(StartLocation,EndLocation);
};

float AMovingPlatform::GetDistanceMoved() const
{
	return FVector::Dist(StartLocation,GetActorLocation());
};

bool AMovingPlatform::ShouldPlatformReturnRotate() const
{
	return (RotationAmount >= MaxRotationBeforeFlip);
};

float AMovingPlatform::GetDistanceRotated() const
{
	return (StartRotation.Vector() | GetActorRotation().Vector());
};