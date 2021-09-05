// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "TankPlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Cannon.h"
#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"
#include "DamageTaker.h"
#include <Particles/ParticleSystemComponent.h>
#include <Components/AudioComponent.h>
#include "MapLoader.h"

// Sets default values
ATurret::ATurret()
{
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health component"));
	HealthComponent->OnDie.AddUObject(this, &ATurret::Die);
	HealthComponent->OnDamaged.AddUObject(this, &ATurret::DamageTaked);

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret body"));
	RootComponent = BodyMesh;

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret turret"));
	TurretMesh->AttachToComponent(BodyMesh, FAttachmentTransformRules::KeepRelativeTransform);

	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Cannon setup point"));
	CannonSetupPoint->AttachToComponent(TurretMesh, FAttachmentTransformRules::KeepRelativeTransform);

	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit collider"));
	HitCollider->SetupAttachment(TurretMesh);

	DestroyEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Destroy Effect"));
	DestroyEffect->SetupAttachment(BodyMesh);

	DamageEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Damage Effect"));
	DamageEffect->SetupAttachment(BodyMesh);

	AudioEffect = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Effect"));
	AudioEffect->SetupAttachment(BodyMesh);

	UStaticMesh* turretMeshTemp = LoadObject<UStaticMesh>(this, *TurretMeshPath);
	if (turretMeshTemp)
		TurretMesh->SetStaticMesh(turretMeshTemp);

	UStaticMesh* bodyMeshTemp = LoadObject<UStaticMesh>(this, *BodyMeshPath);
	if (bodyMeshTemp)
		BodyMesh->SetStaticMesh(bodyMeshTemp);


}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
	if (LinkedMapLoader)
		LinkedMapLoader->SetIsActivated(false);


	FActorSpawnParameters params;
	params.Owner = this;
	Cannon = GetWorld()->SpawnActor<ACannon>(CannonClass, params);
	Cannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	FTimerHandle _targetingTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(_targetingTimerHandle, this, &ATurret::Targeting, TargetingRate, true, TargetingRate);

	
}

void ATurret::Destroyed()
{
	if (Cannon)
		Cannon->Destroy();
}

void ATurret::Targeting()
{
	if (IsPlayerInRange())
	{
		RotateToPlayer();
	}

	if (CanFire() && Cannon && Cannon->IsReadyToFire())
	{
		Fire();
	}
}

void ATurret::RotateToPlayer()
{
	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerPawn->GetActorLocation());
	FRotator currRotation = TurretMesh->GetComponentRotation();
	targetRotation.Pitch = currRotation.Pitch;
	targetRotation.Roll = currRotation.Roll;
	TurretMesh->SetWorldRotation(FMath::Lerp(currRotation, targetRotation, TargetingSpeed));


}

bool ATurret::IsPlayerInRange()
{
	return FVector::Distance(PlayerPawn->GetActorLocation(), GetActorLocation()) <= TargetingRange;
}

bool ATurret::CanFire()
{
	if (!IsPlayerSeen())
		return false;

	FVector targetingDir = TurretMesh->GetForwardVector();
	FVector dirToPlayer = PlayerPawn->GetActorLocation() - GetActorLocation();
	dirToPlayer.Normalize();
	float aimAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(targetingDir, dirToPlayer)));
	return aimAngle <= Accurency;
}

void ATurret::Fire()
{
	if (Cannon)
		Cannon->Fire();
}

void ATurret::TakeDamage(FDamageData DamageData)
{
	UE_LOG(LogTemp, Warning, TEXT("Turret %s taked damage:%f "), *GetName(), DamageData.DamageValue);
}

void ATurret::Die()
{

	Destroy();
	DestroyEffect->ActivateSystem();
	AudioEffect->Play();

	if (LinkedMapLoader)
		LinkedMapLoader->SetIsActivated(true);


}

void ATurret::DamageTaked(float DamageValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Turret %s taked damage:%f Health:%f"), *GetName(), DamageValue, HealthComponent->GetHealth());

}
bool ATurret::IsPlayerSeen()
{
	
	

	FVector playerPos = PlayerPawn->GetActorLocation();
	FVector eyesPos = CannonSetupPoint->GetComponentLocation();

	FHitResult hitResult;
	FCollisionQueryParams traceParams = FCollisionQueryParams(FName(TEXT("FireTrace")), true, this);
	traceParams.bTraceComplex = true;
	//traceParams.AddIgnoredActor(TankPawn);
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

