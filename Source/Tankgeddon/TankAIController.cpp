// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankPawn.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	Initialize();

// 	TankPawn = Cast<ATankPawn>(GetPawn());
// 	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn(); 
// 	MovementAccurency = TankPawn->GetMovementAccurency();
// 
// 	FVector pawnLocation = TankPawn->GetActorLocation();		
// 	TArray<FVector> points = TankPawn->GetPatrollingPoints();
// 	
// 
// 	for (FVector point : points)
// 	{
// 		PatrollingPoints.Add(point + pawnLocation);
// 	}
// 	CurrentPatrolPointIndex = PatrollingPoints.Num() == 0 ? INDEX_NONE : 0;
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!TankPawn)
		Initialize();

	if (!TankPawn)
		return;

	if (CurrentPatrolPointIndex == INDEX_NONE)
	{
		TankPawn->MoveForward(0.f);
		return;

	}
	TankPawn->MoveForward(1.f);

	float rotationValue = GetRotationgValue();
	TankPawn->RotateRight(rotationValue);

	Targeting();

}

float ATankAIController::GetRotationgValue()
{
	FVector currentPoint = PatrollingPoints[CurrentPatrolPointIndex];
	FVector pawnLocation = TankPawn->GetActorLocation();
	if (FVector::Distance(currentPoint, pawnLocation) <= MovementAccurency)
	{
		CurrentPatrolPointIndex++;
		if (CurrentPatrolPointIndex >= PatrollingPoints.Num())
			CurrentPatrolPointIndex = 0;
	}

	FVector moveDirection = currentPoint - pawnLocation;
	moveDirection.Normalize();
	FVector forwardDirection = TankPawn->GetActorForwardVector();
	FVector rightDirection = TankPawn->GetActorRightVector();

	//DrawDebugLine(GetWorld(), pawnLocation, currentPoint, FColor::Green, false, 0.1f, 0, 5);

	float forwardAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(forwardDirection, moveDirection)));
	float rightAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(rightDirection, moveDirection)));

	float rotationValue = 0;
	if (forwardAngle > 5)
		rotationValue = 1;
	if (rightAngle > 90)
		rotationValue = -rotationValue;

	return rotationValue;
}

void ATankAIController::Targeting()
{
	if (CanFire())
		Fire();
	else
		RotateToPlayer();
}

void ATankAIController::RotateToPlayer()
{
	if (IsPlayerInRange())
		TankPawn->RotateTurretTo(PlayerPawn->GetActorLocation());
}

bool ATankAIController::IsPlayerInRange()
{
	return FVector::Distance(TankPawn->GetActorLocation(), PlayerPawn->GetActorLocation()) <= TargetingRange;
}

bool ATankAIController::CanFire()
{
	if (!IsPlayerSeen())
		return false;

	FVector targetingDir = TankPawn->GetTurretForwardVector();
	FVector dirToPlayer = PlayerPawn->GetActorLocation() - TankPawn->GetActorLocation();
	dirToPlayer.Normalize();
	float aimAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(targetingDir, dirToPlayer)));
	return aimAngle <= Accurency;
}

void ATankAIController::Fire()
{
	TankPawn->Fire();
}

bool ATankAIController::IsPlayerSeen()
{
	if (!PlayerPawn)
		Initialize();

		FVector playerPos = PlayerPawn->GetActorLocation();
		FVector eyesPos = TankPawn->GetEyesPosition();

		FHitResult hitResult;
		FCollisionQueryParams traceParams = FCollisionQueryParams(FName(TEXT("FireTrace")), true, this);
		traceParams.bTraceComplex = true;
		traceParams.AddIgnoredActor(TankPawn);
		traceParams.bReturnPhysicalMaterial = false;

		if (GetWorld()->LineTraceSingleByChannel(hitResult, eyesPos, playerPos, ECollisionChannel::ECC_Visibility, traceParams))
		{

			if (hitResult.Actor.Get())
			{
				DrawDebugLine(GetWorld(), eyesPos, hitResult.Location, FColor::Cyan, false, 0.5f, 0, 10);
				return hitResult.Actor.Get() == PlayerPawn;
			}
		}
		DrawDebugLine(GetWorld(), eyesPos, playerPos, FColor::Cyan, false, 0.5f, 0, 10);
		return false;
	
}

void ATankAIController::Initialize()
{
	TankPawn = Cast<ATankPawn>(GetPawn());
	if (TankPawn)
	{
		PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
		FVector pawnLocation = TankPawn->GetActorLocation();
		MovementAccurency = TankPawn->GetMovementAccurency();
		TArray<FVector> points = TankPawn->GetPatrollingPoints();
		for (FVector point : points)
		{
			PatrollingPoints.Add(point);
		}
		CurrentPatrolPointIndex = 0;
	}
}

