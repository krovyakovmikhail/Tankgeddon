// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Engine/Engine.h"


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
void ACannon::BeginPlay()
{

	Super::BeginPlay();
	Reload();
}

// Called every frame
void ACannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//������� � ��������� ���-�� ��������.
	//GEngine->AddOnScreenDebugMessage(10, 1, FColor::Yellow, NumberOfShells);
}

void ACannon::Fire()
{
	if (!ReadyToFire)
	{
		return;
	}
	ReadyToFire = false;

	if (Type == ECannonType::FireProjectile)
	{
	if (NumberOfShells > 0)

		{
			GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - projectile");
			NumberOfShells--; //���������� ������� � -1 ������.
		}
		
		else //��� ��������
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Blue, "no shells!");
	}
	else //
	{
		if (NumberOfShells > 0)
		{
			GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - trace");
			NumberOfShells--; //���������� ������� � -1 ������.
		}
		
		else //��� ��������
			GEngine->AddOnScreenDebugMessage(10, 1, FColor::Blue, "no shells!");
	}

	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1 / FireRate, false);

}

//FireSpecial
void ACannon::FireSpecial()
{
	if (!ReadyToFire)
	{
		return;
	}
	ReadyToFire = false;



	if (NumberOfSpecialShells > 0)
	{
	GEngine->AddOnScreenDebugMessage(10, 1, FColor::Red, "FireSpecial");
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1 / FireRate, false);

    NumberOfSpecialShells --;
	}
	else //��� ��������
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Blue, "no shells!");
};


bool ACannon::IsReadyToFire()
{
	return ReadyToFire;
}

void ACannon::Reload()
{
	ReadyToFire = true;
}
