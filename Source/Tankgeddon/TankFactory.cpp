// Fill out your copyright notice in the Description page of Project Settings.


#include "TankFactory.h"
#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MapLoader.h"


// Sets default values
ATankFactory::ATankFactory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceneComp;

	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Building Mesh"));
	BuildingMesh->SetupAttachment(sceneComp);

	TankSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Cannon setup point"));
	TankSpawnPoint->AttachToComponent(sceneComp, FAttachmentTransformRules::KeepRelativeTransform);

	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit collider"));
	HitCollider->SetupAttachment(sceneComp);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health component"));
	HealthComponent->OnDie.AddUObject(this, &ATankFactory::Die);
	HealthComponent->OnDamaged.AddUObject(this, &ATankFactory::DamageTaked);

	DestroyEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Destroy Effect"));
	DestroyEffect->SetupAttachment(HitCollider);
	AudioEffect = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Effect"));
	AudioEffect->SetupAttachment(HitCollider);
	SpawnTankEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Damage Effect"));
	SpawnTankEffect->SetupAttachment(HitCollider);

	

}

void ATankFactory::TakeDamage(FDamageData DamageData)
{
	HealthComponent->TakeDamage(DamageData);
}

// Called when the game starts or when spawned
void ATankFactory::BeginPlay()
{
	Super::BeginPlay();

	if (LinkedMapLoader)
		LinkedMapLoader->SetIsActivated(false);

	FTimerHandle _targetingTimerHandle;

	GetWorld()->GetTimerManager().SetTimer(_targetingTimerHandle, this, &ATankFactory::SpawnNewTank, SpawnTankRate, true, SpawnTankRate);

	
}

void ATankFactory::SpawnNewTank()
{
	
	SpawnTankEffect->ActivateSystem(); // активируем эффект
	if (SpawnTank) 
	{
		FTransform spawnTransform(TankSpawnPoint->GetComponentRotation(), TankSpawnPoint->GetComponentLocation(), FVector(1));
		ATankPawn* newTank = GetWorld()->SpawnActorDeferred<ATankPawn>(SpawnTankClass, spawnTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);


		//эффект создания танка..
		


		newTank->SetPatrollingPoints(TankWayPoints);
		//
		UGameplayStatics::FinishSpawningActor(newTank, spawnTransform);
	}
	


	
}

void ATankFactory::Die()
{
	// добавить ссылку на другой меш. заменяем меш на другой
	//BuildingMesh = StaticMesh'/Game/StarterContent/Architecture/Floor_400x400.Floor_400x400';
	
	//дестроим компонент стрелку спаун поинт. - ?
	//сделаю булеву через которую можно отключить спаун.
	SpawnTank = false;
	DestroyEffect->ActivateSystem();
	AudioEffect->Play();

	if (LinkedMapLoader)
		LinkedMapLoader->SetIsActivated(true);
}

void ATankFactory::DamageTaked(float DamageValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Factory %s taked damage:%f Health:%f"), *GetName(), DamageValue, HealthComponent->GetHealth());

}

// Called every frame
void ATankFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

