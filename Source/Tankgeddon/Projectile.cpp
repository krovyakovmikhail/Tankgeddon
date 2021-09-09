// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "DamageTaker.h"

// Sets default values
AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	USceneComponent* sceeneCpm = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceeneCpm;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnMeshOverlapBegin);
	Mesh->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
}

// Called when the game starts or when spawned


void AProjectile::TakeDamageOrAddImpulse(AActor* Actor)
{
	IDamageTaker* damageTakerActor = Cast<IDamageTaker>(Actor);
	if (damageTakerActor)
	{
		FDamageData damageData;
		damageData.DamageValue = Damage;
		damageData.Instigator = GetOwner();
		damageData.DamageMaker = this;

		damageTakerActor->TakeDamage(damageData);
	}
	else
	{
		UPrimitiveComponent* mesh = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
		if (mesh)
		{
			if (mesh->IsSimulatingPhysics())
			{
				FVector forceVector = Actor->GetActorLocation() - GetActorLocation();
				forceVector.Normalize();
				mesh->AddImpulse(forceVector * PushForce, NAME_None, true);
			}
		}
	}
}

void AProjectile::Explode(bool bExpl)
{
	if (bExpl)
	{
		FVector startPos = GetActorLocation();
		FVector endPos = startPos + FVector(0.1f);

		FCollisionShape Shape = FCollisionShape::MakeSphere(ExplodeRadius);
		FCollisionQueryParams params = FCollisionQueryParams::DefaultQueryParam;
		params.AddIgnoredActor(this);
		params.bTraceComplex = true;
		params.TraceTag = "Explode Trace";
		TArray<FHitResult> AttackHit;

		FQuat Rotation = FQuat::Identity;

		bool sweepResult = GetWorld()->SweepMultiByChannel
		(
			AttackHit,
			startPos,
			endPos,
			Rotation,
			ECollisionChannel::ECC_Visibility,
			Shape,
			params
		);

		GetWorld()->DebugDrawTraceTag = "Explode Trace";

		if (sweepResult)
		{
			for (FHitResult hitResult : AttackHit)
			{
				AActor* otherActor = hitResult.GetActor();
				if (!otherActor)
					continue;

				TakeDamageOrAddImpulse(otherActor);

			}
		}
	}
	
}




void AProjectile::Start()
{
	GetWorld()->GetTimerManager().SetTimer(MovementTimerHandle, this, &AProjectile::Move, MoveRate, true, MoveRate);
}

void AProjectile::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
									 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	UE_LOG(LogTemp, Warning, TEXT("Projectile %s collided with %s. "), *GetName(), *OtherActor->GetName());
	

	AActor* owner = GetOwner();
	AActor* ownerByOwner = owner != nullptr ? owner->GetOwner() : nullptr;
	UPrimitiveComponent* mesh = Cast<UPrimitiveComponent>(OtherActor->GetRootComponent());
	FVector forceVector = OtherActor->GetActorLocation() - GetActorLocation();
	forceVector.Normalize();

	if (OtherActor != owner && OtherActor != ownerByOwner)
	{
		IDamageTaker* damageTakerActor = Cast<IDamageTaker>(OtherActor);
		if (damageTakerActor)
		{
			FDamageData damageData;
			damageData.DamageValue = Damage;
			damageData.Instigator = owner;
			damageData.DamageMaker = this;

			damageTakerActor->TakeDamage(damageData);



			// L8 / task 1 / Попробуйте для передачи силы на объект при касании снаряда воспользоваться методами AddForce.
			// попробуем применять силу на танки и туррели.			
			if (mesh)
			{
				if (mesh->IsSimulatingPhysics())
				{
					mesh->AddImpulse(forceVector * PushForce, NAME_None, true);
				}
			}
		}
		else
		{
			
			if (mesh)
			{
				if (mesh->IsSimulatingPhysics())
				{
				mesh->AddImpulse(forceVector * PushForce, NAME_None, true);
				}
			}
		}

		//Добавьте отрабатывание взрыва не только при касании поверхности, но и при любом столкновении снаряда с объектами.
		Explode(bExplosion); //Вызываем взрыв в событии OnMeshOverlapBegin. с помощью параметра bExplosion проверяем запускать взрыв или нет. 

		Destroy();
	}


}

void AProjectile::Move()
{
	FVector nextPosition = GetActorLocation() + GetActorForwardVector() * MoveSpeed * MoveRate;
	SetActorLocation(nextPosition);
}

