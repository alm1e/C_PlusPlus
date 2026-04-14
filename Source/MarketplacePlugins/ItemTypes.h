// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"


#include "ItemTypes.generated.h"

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FName ItemName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    UTexture2D* ItemIcon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    int32 MaxStackSize;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<AActor> ItemClass;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EItemType ItemType;

    FItemData()
    {
        ItemName = FName("Empty");
        ItemIcon = nullptr;
        MaxStackSize = 100;
    }
};
UENUM(BlueprintType)
enum class EItemClass : unit8
{
    None, 
    Weapon,
    Feet,
    Backpack,
    Head, 
    Consumable
    
};