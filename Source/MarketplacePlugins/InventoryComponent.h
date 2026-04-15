#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Net/UnrealNetwork.h"
#include "ItemTypes.h"
#include "InventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FItemData ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 Quantity = 0;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MARKETPLACEPLUGINS_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(ReplicatedUsing = OnRep_InventorySlots, BlueprintReadOnly, Category = "Inventory")
	TArray<FInventorySlot> InventorySlots;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	int32 MaxInventorySize = 20;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryUpdated OnInventoryUpdated;

	UFUNCTION()
	void OnRep_InventorySlots();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool TryAddItem(const FItemData& NewItem, int32 Amount);

	// ---------- Blueprint requests ----------
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RequestDropItem(int32 SlotIndex, int32 AmountToDrop);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RequestSwapSlots(int32 FromIndex, int32 ToIndex);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RequestDropAllItemsOfSameType(FName ItemName);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RequestSortInventory();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RequestUpgradeInventorySize(int32 AdditionalSlots);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RequestSplitStack(int32 SlotIndex);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RequestAddItem(FItemData NewItem, int32 Amount);

	// ---------- Server RPC ----------
	UFUNCTION(Server, Reliable)
	void ServerDropItem(int32 SlotIndex, int32 AmountToDrop);

	UFUNCTION(Server, Reliable)
	void ServerSwapSlots(int32 FromIndex, int32 ToIndex);

	UFUNCTION(Server, Reliable)
	void ServerDropAllItemsOfSameType(FName ItemName);

	UFUNCTION(Server, Reliable)
	void ServerSortInventory();

	UFUNCTION(Server, Reliable)
	void ServerUpgradeInventorySize(int32 AdditionalSlots);

	UFUNCTION(Server, Reliable)
	void ServerSplitStack(int32 SlotIndex);

	UFUNCTION(Server, Reliable)
	void ServerAddItem(FItemData NewItem, int32 Amount);

	// ---------- Server-side gameplay ----------
	bool AddItem(const FItemData& NewItem, int32 Amount);
	bool DropItem_Internal(int32 SlotIndex, int32 AmountToDrop);
	void SwapSlots_Internal(int32 FromIndex, int32 ToIndex);
	void DropAllItemsOfSameType_Internal(FName ItemName);
	void SortInventory_Internal();
	void UpgradeInventorySize_Internal(int32 AdditionalSlots);
	int32 SplitStack_Internal(int32 SlotIndex);

private:
	void BroadcastInventoryUpdated();
	void EnsureInventorySize();
};