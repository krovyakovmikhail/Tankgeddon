// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATankPawn;
/**
 * 
 */
UCLASS()
class TANKGEDDON_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
	

	UPROPERTY()
		ATankPawn* TankPawn;
	UPROPERTY()
		APawn* PlayerPawn;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Patrol points", Meta = (MakeEditWidget = true))
	TArray<FVector> PatrollingPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Accurency")
		float MovementAccurency;


	int32 CurrentPatrolPointIndex = INDEX_NONE;

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
		float TargetingRange = 1000;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
		float TargetingSpeed = 0.3f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
		float Accurency = 10;

	

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	float GetRotationgValue();
	void Targeting();
	void RotateToPlayer();
	bool IsPlayerInRange();
	bool CanFire();
	void Fire();
	bool IsPlayerSeen();

};
