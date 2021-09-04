// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "TankPlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/ArrowComponent.h"
#include <Particles/ParticleSystemComponent.h>
#include <Components/AudioComponent.h>

class ATankPawn;
class ACannon;
class TankAIController;


DECLARE_LOG_CATEGORY_EXTERN(TankLog, All, All);
DEFINE_LOG_CATEGORY(TankLog);
// Sets default values


ATankPawn::ATankPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank body"));
	RootComponent = BodyMesh;

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank turret"));
	TurretMesh->SetupAttachment(BodyMesh);

	DestroyEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Destroy Effect"));
	DestroyEffect->SetupAttachment(BodyMesh);

	DamageEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Damage Effect"));
	DamageEffect->SetupAttachment(BodyMesh);

	AudioEffect = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Effect"));
	AudioEffect->SetupAttachment(BodyMesh);

	//Cannon
	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Cannon setup point"));
	CannonSetupPoint->AttachToComponent(TurretMesh, FAttachmentTransformRules::KeepRelativeTransform);

	


	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm"));
	SpringArm->SetupAttachment(BodyMesh);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health component"));
	HealthComponent->OnDie.AddUObject(this, &ATankPawn::Die);
	HealthComponent->OnDamaged.AddUObject(this, &ATankPawn::DamageTaked);

	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit collider"));
	HitCollider->SetupAttachment(BodyMesh);

}

FVector ATankPawn::GetTurretForwardVector()
{
	return TurretMesh->GetForwardVector();
}
FVector ATankPawn::GetEyesPosition()
{
	return CannonSetupPoint->GetComponentLocation();
}

// Called when the game starts or when spawned
void ATankPawn::BeginPlay()
{

	Super::BeginPlay();
	TankController = Cast<ATankPlayerController>(GetController());

	//Начало игры - загружаем пушку. 
	SetupCannon(CannonClass);


	//Начало игры - загружаем пушку во второй слот. 	
	FActorSpawnParameters params;
	params.Instigator = this;
	params.Owner = this;
	Cannonslot2 = GetWorld()->SpawnActor<ACannon>(CannonClass2, params);
	Cannonslot2->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	
}

// Called every frame
void ATankPawn::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

	// Tank movement
	FVector currentLocation = GetActorLocation();
	FVector forwardVector = GetActorForwardVector();
	FVector movePosition = currentLocation + forwardVector * MoveSpeed * _targetForwardAxisValue * DeltaTime;
	SetActorLocation(movePosition, true);

	//Поворот танка
	CurrentRightAxisValue = FMath::Lerp(CurrentRightAxisValue, TargetRotateAxisValue, InterpolationKey);

	//UE_LOG(LogTemp, Warning, TEXT("CurrentRightAxisValue = %f TargetRightAxisValue = %f"), CurrentRightAxisValue, TargetRotateAxisValue);

	float yawRotation = RotationSpeed * CurrentRightAxisValue * DeltaTime;
	FRotator currentRotation = GetActorRotation();
	yawRotation = currentRotation.Yaw + yawRotation;
	FRotator newRotation = FRotator(0, yawRotation, 0);
	SetActorRotation(newRotation);

	// Поворот турелли.
	if (TankController)
	{
		FVector mousePos = TankController->GetMousePos();
		RotateTurretTo(mousePos);
	}

};
	
	

// поворот туррели танка на игрока
void ATankPawn::RotateTurretTo(FVector TargetPosition)
{
	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetPosition);
	FRotator currRotation = TurretMesh->GetComponentRotation();
	targetRotation.Pitch = currRotation.Pitch;
	targetRotation.Roll = currRotation.Roll;
	TurretMesh->SetWorldRotation(FMath::Lerp(currRotation, targetRotation, TurretRotationInterpolationKey));
}

void ATankPawn::MoveForward(float AxisValue)
{
	_targetForwardAxisValue = AxisValue;
}

void ATankPawn::RotateRight(float AxisValue)
{
	TargetRotateAxisValue = AxisValue;
}

//Cannon
void ATankPawn::SetupCannon(TSubclassOf<ACannon> inClassCannon)
{
	if (Cannonslot1) //сбрасывать пушку и крепить из подобранного бокса будем на 1-й слот (второй сохраняется всегда.)
	{
		Cannonslot1->Destroy();
	}

	FActorSpawnParameters params;
	params.Instigator = this;
	params.Owner = this;
	Cannonslot1 = GetWorld()->SpawnActor<ACannon>(inClassCannon, params);
	Cannonslot1->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);


}

void ATankPawn::ChangeCannon()  //замена пушки
{
	ACannon* Cannon; //Время жизни объекта Cannon будет ограничено функцие CancgeCannon/ 

	Cannon = Cannonslot1;

	Cannonslot1 = Cannonslot2;
	Cannonslot2 = Cannon;	
}

void ATankPawn::Fire()
{
	if (Cannonslot1)
	{
		Cannonslot1->Fire();
	}
}

void ATankPawn::FireSpecial()
{
	if (Cannonslot1)
	{
		Cannonslot1->FireSpecial();
	}
}

void ATankPawn::TakeDamage(FDamageData DamageData)
{
	HealthComponent->TakeDamage(DamageData);
	DamageEffect->ActivateSystem();
	AudioEffect->Play();
}

void ATankPawn::Die()
{
	Destroy();
	DestroyEffect->ActivateSystem();
	AudioEffect->Play();
}

void ATankPawn::DamageTaked(float DamageValue)
{
	UE_LOG(TankLog, Warning, TEXT("Tank %s taked damage:%f Health:%f"), *GetName(), DamageValue, HealthComponent->GetHealth());
}






