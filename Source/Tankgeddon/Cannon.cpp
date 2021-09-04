// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Engine/Engine.h"
#include "Projectile.h"
#include "Engine/World.h"
#include "DamageTaker.h"
#include "HealthComponent.h"
#include "DrawDebugHelpers.h"


class AProjectile;

// Sets default values
ACannon::ACannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* sceeneCpm = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceeneCpm;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannon mesh"));
	Mesh->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn point"));
	ProjectileSpawnPoint->SetupAttachment(Mesh);


}

// Called when the game starts or when spawned

void ACannon::AddShells(int32 &shells)
{
	NumberOfShells = NumberOfShells + shells;
};

void ACannon::Fire()
{	

	if (!ReadyToFire || NumberOfShells <= 0) // Идем в если когда неперезаряжен или количество снарядов 0
	{		
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Blue, "no shells!");
		return;		
	}
	ReadyToFire = false;

	// FIRE
	if (Type == ECannonType::FireProjectile)
	{
			GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - projectile");
			AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
			if (projectile)
			{

				projectile->Start(); // выпускаем снаряд 
			}
			GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1 / FireRate, false); 
			NumberOfShells--; // -1 снаярд.

	}
	else if (Type == ECannonType::FireTrace) //Use Trace
	{	
		AActor* owner = GetOwner();
		AActor* ownerByOwner = owner != nullptr ? owner->GetOwner() : nullptr;
		AActor* OtherActor = nullptr; //нужно получить цель пересечения луча.

		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - trace");
		

		FHitResult hitResult;
		FCollisionQueryParams traceParams = FCollisionQueryParams(FName(TEXT("FireTrace")), true, this);
		traceParams.bTraceComplex = true;
		traceParams.bReturnPhysicalMaterial = false;

		FVector start = ProjectileSpawnPoint->GetComponentLocation();
		FVector end = ProjectileSpawnPoint->GetForwardVector() * FireRange + start;

		if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_Visibility, traceParams))
		{
			DrawDebugLine(GetWorld(), start, hitResult.Location, FColor::Red, false, 0.3f, 0,3);

			

			UE_LOG(LogTemp, Warning, TEXT(" %s collided with %s. "), *GetName(), *OtherActor->GetName());

			if (hitResult.Actor.Get())
			{
				if (OtherActor != owner && OtherActor != ownerByOwner)
				{
					IDamageTaker* damageTakerActor = Cast<IDamageTaker>(OtherActor);
					if (damageTakerActor)
					{
						FDamageData damageData;
						damageData.DamageValue = FireDamage;
						damageData.Instigator = owner;
						damageData.DamageMaker = this;

						damageTakerActor->TakeDamage(damageData);
					}
					else
					{
						OtherActor->Destroy();
					}

					Destroy();
				}
			}
		}
		else
		{
			DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 0.3f, 0,3);
		}

		GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1 / FireRate, false);

		NumberOfShells--; // -1 снаярд.		
	}
	else //Use autofire //Нажимаем ЛКМ 1 раз: появляется снаряд, задержка, появляется снаряд...
	{
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2, FColor::Purple, "Use autofire", true);
			AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
			if (projectile)
			{
				projectile->Start(); // выпускаем снаряд 
			}
		
			if (autofirelenth > 0) 
			{
				autofirelenth--;
				ReadyToFire = true;
				GetWorld()->GetTimerManager().SetTimer(AutiFiretimer, this, &ACannon::Fire, 0.2, false); 
				
				
			}
		

			GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1 / FireRate, false); // Вызывается перезарядка 
		
			NumberOfShells--; 
			
	}

	

}
//FireSpecial
void ACannon::FireSpecial()
{
	if (!ReadyToFire)
	{
		return;
	}
	ReadyToFire = false;


	
	if (NumberOfSpecialShells > 0 && autofirelenth > 0)
	{
	GEngine->AddOnScreenDebugMessage(10, 1, FColor::Red, "FireSpecial");

	

	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1 / FireRate, false);
	
	autofirelenth--;
	FireSpecial(); // пока autofirelenth не дойдет до 0 будет повторно вызывася медод спишлфайр 			

    NumberOfSpecialShells --;
	
	autofirelenth = 3;

	}
	else //нет снарядов
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Blue, "no shells!");
};
bool ACannon::IsReadyToFire()
{
	return ReadyToFire;
}
void ACannon::Reload()  
{

		ReadyToFire = true;
		autofirelenth = 2;
		
}
void ACannon::BeginPlay()
{

	Super::BeginPlay();
	Reload();

}

