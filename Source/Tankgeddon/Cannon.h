// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameStructs.h"
#include "GameFramework/Actor.h"
#include "Cannon.generated.h"

class UArrowComponent;


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
		ECannonType Type = ECannonType::FireAuto;

	FTimerHandle ReloadTimerHandle;

	bool ReadyToFire = false;

	//Количество снарядов по-умолчанию пока поставим в пушку 10. Потом посмотрит как будет. И отдельно количество SpecialShells
	int NumberOfShells = 10;

	int NumberOfSpecialShells = 10;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	//Reload
	void Reload();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void Fire();

	bool IsReadyToFire();


	// FireSpecial()
	void FireSpecial();
};
