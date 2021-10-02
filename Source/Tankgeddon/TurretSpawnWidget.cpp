// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretSpawnWidget.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <Tankgeddon/TankPlayerController.h>


void UTurretSpawnWidget::NativePreConstruct()
{
    if (TurretText)
    {
        TurretText->SetText(TurretName);
    }
 
}
void UTurretSpawnWidget::NativeConstruct()
{
    Super::NativeConstruct();

    PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

    ATankPlayerController* Controller =   Cast<ATankPlayerController>(PlayerController);

    if (Controller)
    {
        Controller->OnMouseButtonUp.AddUObject(this, &UTurretSpawnWidget::OnMouseButtonUp);
    }
    
}

void UTurretSpawnWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (SpawnedActor && PlayerController)
    {   
        FVector Loc, Dir;
        
        PlayerController->DeprojectMousePositionToWorld(Loc, Dir);



        FHitResult HitResult;
        FCollisionQueryParams Params = FCollisionQueryParams::DefaultQueryParam;
        Params.AddIgnoredActor(PlayerController->GetPawn());
        GetWorld()->LineTraceSingleByChannel(HitResult, Loc, Loc + Dir * 100000, ECollisionChannel::ECC_WorldStatic);

        if (HitResult.Actor.Get())
        {
            HitResult.Location.Z = 0;

          SpawnedActor->SetActorLocation(HitResult.Location);
        }
    }

}

FReply UTurretSpawnWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
    {
        SpawnedActor = GetWorld()->SpawnActor(SpawnedActorClass);
    }
    return FReply::Handled();
}

void UTurretSpawnWidget::OnMouseButtonUp()
{
    SpawnedActor = nullptr;
}
