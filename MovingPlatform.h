// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class COURSEPROJECT2_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere,Category="Moving")
	float PlatformVelocity = 100;

	UPROPERTY(EditAnywhere,Category="Moving")
	FVector EndLocation = FVector(0,0,0);

	UPROPERTY(EditAnywhere,Category="Moving")
	bool EndLocationIsRelative = true;

	UPROPERTY(EditAnywhere,Category="Rotation")
	FRotator RotationVelocity;

	UPROPERTY(EditAnywhere,Category="Rotation")
	float MaxRotationBeforeFlip = 0;

	FVector StartLocation;
	FString NameString;
	FRotator StartRotation;
	float RotationAmount;

	void MovePlatform(float DeltaTime);
	void RotatePlatform(float DeltaTime);

	bool ShouldPlatformReturn() const;
	float GetDistanceMoved() const;

	bool ShouldPlatformReturnRotate() const;
	float GetDistanceRotated() const;
};
