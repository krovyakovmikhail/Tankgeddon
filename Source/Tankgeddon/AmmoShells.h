// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Cannon.h"
#include "TankPawn.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AmmoShells.generated.h"


UCLASS()
class TANKGEDDON_API AAmmoShells : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Variables")
	int32 Shells = 10;


public:
	// Sets default values for this actor's properties
	AAmmoShells();

protected:
	UFUNCTION()
		void OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
