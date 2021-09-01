// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameStructs.h"
#include "GameFramework/Actor.h"
#include "DamageTaker.h"
#include "Cannon.generated.h"



class UArrowComponent;
class AProjectile;


UCLASS()
class TANKGEDDON_API ACannon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACannon();

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		float FireRate = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		float FireRange = 1000;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		float FireDamage = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		ECannonType Type = ECannonType::FireProjectile;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		int32 NumberOfShells = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		int32 NumberOfSpecialShells = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		int32 autofirelenth = 2;



	FTimerHandle ReloadTimerHandle;
	FTimerHandle AutiFiretimer;


	bool ReadyToFire = false;

	//���������� �������� ��-��������� ���� �������� � ����� 10. ����� ��������� ��� �����. � �������� ���������� SpecialShells
	
	
	 // ������������ ��� SpecialFire();
	

	void Reload();	
	

public:	
	
	void Fire();
	bool IsReadyToFire();
	// FireSpecial()
	void FireSpecial();
	virtual void BeginPlay() override;
	void AddShells (int32 &shells);
};

