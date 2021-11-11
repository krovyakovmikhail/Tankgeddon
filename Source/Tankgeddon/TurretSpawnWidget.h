// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Actor.h"
#include <Runtime/UMG/Public/Components/TextBlock.h>
#include "TurretSpawnWidget.generated.h"


/**
 * 
 */
UCLASS()
class TANKGEDDON_API UTurretSpawnWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	FReply NativeOnMouseButtonDown(const FGeometry& InGeometry,	const FPointerEvent& InMouseEvent) override;


    UPROPERTY(EditAnywhere)
        FText TurretName;  
   

    UPROPERTY(meta = (BindWidget))
        UTextBlock* TurretText;
       


protected:

    UPROPERTY(EditAnywhere)
        TSubclassOf<AActor> SpawnedActorClass;

    UPROPERTY()
        AActor* SpawnedActor;

    UPROPERTY()
        APlayerController* PlayerController;

    void OnMouseButtonUp();
};
