#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "InventoryItem.generated.h"

UENUM()
enum class EEquipSlot :uint8
{
    ES_None,
    ES_Muzzle,
    ES_LeftCaterpillar,
    ES_RightCaterpillar,
    ES_Turret,
    ES_Bombs,
};

UENUM()
enum class EItemType : uint8
{
    IT_Miscellaneous,
    IT_Currency,
    IT_Equipment,
    IT_Consumable
};

UENUM()
enum class EItemRarity : uint8
{
    IR_Common,
    IR_Uncommon,
    IR_Rare,
    IR_Epic,
    IR_Legendary
};

USTRUCT(BlueprintType)
struct FInventoryItemInfo : public FTableRowBase
{
    GENERATED_BODY()

public:
    // tech info
    UPROPERTY(EditAnywhere, Category = "General")
    FName ID;
    
    UPROPERTY(EditAnywhere, Category = "General")
    EEquipSlot EquipSlot;

    // text info
    UPROPERTY(EditAnywhere, Category = "General")
    FText Name;
    UPROPERTY(EditAnywhere, Category = "General")
    FText Description;

    // enums
    UPROPERTY(EditAnywhere, Category = "Typing")
    EItemType Type;
    UPROPERTY(EditAnywhere, Category = "Typing")
    EItemRarity Rarity;

    // visual representation
    UPROPERTY(EditAnywhere, Category = "Visual")
    TSoftObjectPtr<UTexture2D> Icon;
    UPROPERTY(EditAnywhere, Category = "Visual")
    TSoftObjectPtr<UStaticMesh> Mesh;

    // stats
    UPROPERTY(EditAnywhere, Category = "Stats")
    int32 Damage;
    UPROPERTY(EditAnywhere, Category = "Stats")
    int32 Armor;
    UPROPERTY(EditAnywhere, Category = "Stats")
    int32 Intelligence;
};

USTRUCT(BlueprintType)
struct FInventorySlotInfo
{
    GENERATED_BODY()

public:
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "General")
    FName ID;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "General")
    int32 Count;
};