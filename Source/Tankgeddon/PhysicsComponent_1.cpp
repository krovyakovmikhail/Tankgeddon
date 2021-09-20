// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicsComponent_1.h"

// Sets default values for this component's properties
UPhysicsComponent_1::UPhysicsComponent_1()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.	// ...
}


TArray<FVector> UPhysicsComponent_1::GenerateTrajectory(FVector StartPos, FVector Velocity, float MaxTime, float TimeStep, float MinZValue)
{
	TArray<FVector> trajectory;
	FVector gravityVector(0, 0, Gravity);
	for (float time = 0; time < MaxTime; time = time + TimeStep)
	{
		FVector position = StartPos + Velocity * time + gravityVector * time * time / 2;
		if (position.Z <= MinZValue)
			break;

		trajectory.Add(position);
	}

	return trajectory;
}
