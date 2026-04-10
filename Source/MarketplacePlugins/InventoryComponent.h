// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemTypes.h"


#include "InventoryComponent.generated.h"



USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FItemData ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 Quantity;

	FInventorySlot()
	{
		Quantity = 0;
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MARKETPLACEPLUGINS_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FInventorySlot> InventorySlots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 MaxInventorySize = 20;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(FItemData NewItem, int32 Amount);

	UPROPERTY(BlueprintAssignable, Category="Inventory")
	FOnInventoryUpdated OnInventoryUpdated;

	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool DropItem(int32 SlotIndex, int32 AmountToDrop);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SwapSlots(int32 FromIndex, int32 ToIndex);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void DropAllItemsOfSameType(FName ItemName);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SortInventory();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void UpgradeInventorySize(int32 AdditionalSlots);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int32 SplitStack(int32 SlotIndex);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	
};
