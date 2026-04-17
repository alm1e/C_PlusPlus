
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemTypes.generated.h"

class UTexture2D;
class AActor;

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

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    TSubclassOf<AActor> ItemClass;

    FItemData()
    {
        ItemName = FName("Empty");
        ItemIcon = nullptr;
        MaxStackSize = 100;
        ItemClass = nullptr;
    }
};
