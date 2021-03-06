/// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Cannon.h"
#include "CoreMinimal.h"
#include "DamageTaker.h"
//#include "EquipInventoryComponent.h"
#include "HealthComponent.h"
#include "MyPlugin/Public/InventoryComponent.h"
#include "MyPlugin/Public/InventoryManagerComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "Particles/ParticleSystemComponent.h"

#include "Engine/TargetPoint.h"
#include "TankPawn.generated.h"

class UParticleSystemComponent;
class UAudioComponent;
class UStaticMeshComponent;
class UCameraComponent;
class USpringArmComponent;
class ATankPlayerController;
class ACannon;

UCLASS()
class TANKGEDDON_API ATankPawn : public APawn, public IDamageTaker

{
	GENERATED_BODY()


protected:

	UPROPERTY(EditDefaultsOnly)
	UInventoryComponent * InventoryComponent;
	UPROPERTY(EditDefaultsOnly)
	UInventoryManagerComponent * InventoryManagerComponent;
	
	// UPROPERTY(EditDefaultsOnly)
	// UEquipInventoryComponent * EquipmentInventoryComponent;


	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Patrol points", Meta = (MakeEditWidget = true))
		TArray<ATargetPoint*> PatrollingPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Accurency")
		float MovementAccurency = 50;


	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* BodyMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		USpringArmComponent* SpringArm;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UCameraComponent* Camera;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UHealthComponent* HealthComponent;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* HitCollider;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* DestroyEffect;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* DamageEffect;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UAudioComponent* AudioEffect;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float MoveSpeed = 100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float RotationSpeed = 100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float InterpolationKey = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret|Speed")
		float TurretRotationInterpolationKey = 0.5f;

	UPROPERTY()
		ATankPlayerController* TankController;

	//Cannon
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* CannonSetupPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret|Cannon")
		TSubclassOf<ACannon> CannonClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret|Cannon")
		TSubclassOf<ACannon> CannonClass2;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Health/Die")
		bool bDied = false;

	



	float _targetForwardAxisValue;	
	float TargetRotateAxisValue;
	float CurrentRightAxisValue;


public:
	// Sets default values for this pawn's properties
	ATankPawn();

	UFUNCTION()
	TArray<FVector> GetPatrollingPoints();

	void SetPatrollingPoints(const TArray<ATargetPoint*>& NewPatrollingPoints);

	FVector GetEyesPosition();

	// ????????????????????? 2 ??????????????? ????????? ??????????????????????????? ???????????????. 
	UPROPERTY()
		ACannon* Cannonslot1;
	UPROPERTY()
		ACannon* Cannonslot2;

	// move and rotation
	UFUNCTION()
		void MoveForward(float AxisValue);
	UFUNCTION()
		void RotateRight(float AxisValue);

	//FIRE
	UFUNCTION()
		void Fire();

	UFUNCTION()
		void FireSpecial();

	UFUNCTION()
		void TakeDamage(FDamageData DamageData);

	UFUNCTION()
		void SetupCannon(TSubclassOf<ACannon> inClassCannon);

	UFUNCTION()
		void ChangeCannon();

	UFUNCTION(BlueprintImplementableEvent)
		void MyBPEvent();    // ??????????????? ???????????????
	

	UFUNCTION()
		float GetMovementAccurency() 
	{ 
		return MovementAccurency; 
	};

	UFUNCTION()
		FVector GetTurretForwardVector();

	UFUNCTION()
		void RotateTurretTo(FVector TargetPosition);


	virtual void Tick(float DeltaTime) override;
	
	void EquipItem (EEquipSlot, FName ItemId);
	void UnequipItem(EEquipSlot, FName ItemId);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		void Die();

	UFUNCTION()
		void DamageTaked(float DamageValue);


};
