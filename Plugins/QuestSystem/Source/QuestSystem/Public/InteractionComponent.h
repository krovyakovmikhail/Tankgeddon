// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "InteractionComponent.generated.h"


UCLASS( ClassGroup=(Collision), meta=(BlueprintSpawnableComponent) , DisplayName= "interaction Colision")
class QUESTSYSTEM_API UInteractionComponent : public UBoxComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractionComponent();
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> InteractMessageWidget;
		
	UPROPERTY()
    UUserWidget* InteractMessage;

	UPROPERTY()
	AActor * ActorToInteract;

	UFUNCTION()
	void OnInteractionCompBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	UFUNCTION()
	void OnInteractionCompEndOverlap(UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	void interact ();



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
