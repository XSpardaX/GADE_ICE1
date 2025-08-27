// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpeedPickup.generated.h"

UCLASS()
class GADE_ICE1_API ASpeedPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpeedPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

public:	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* Mesh;

	// Pickup properties
	UPROPERTY(EditAnywhere, Category = "Pickup")
	float BoostAmount = 600.0f; 

	UPROPERTY(EditAnywhere, Category = "Pickup")
	float BoostDuration = 5.0f; 

};
