// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}


void UInventoryComponent::BeginPlay()
{
    Super::BeginPlay();

    InventorySlots.SetNum(MaxInventorySize);
}


void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
// AddItem implementation
bool UInventoryComponent::AddItem(FItemData NewItem, int32 Amount)
{
    for (FInventorySlot& Slot : InventorySlots)
    {
        if (Slot.ItemData.ItemName == NewItem.ItemName)
        {
            int32 AvailableSpace = Slot.ItemData.MaxStackSize - Slot.Quantity;
            if (AvailableSpace > 0)
            {
                int32 AmountToAdd = FMath::Min(Amount, AvailableSpace);
                Slot.Quantity += AmountToAdd;
                Amount -= AmountToAdd;

                if (Amount <= 0) {
                    OnInventoryUpdated.Broadcast();
                    return true;
                }
            }
        }
    }

    for (FInventorySlot& Slot : InventorySlots)
    {
        if (Slot.Quantity == 0)
        {
            Slot.ItemData = NewItem;
            int32 AmountToAdd = FMath::Min(Amount, NewItem.MaxStackSize);
            Slot.Quantity = AmountToAdd;
            Amount -= AmountToAdd;
            if (Amount <= 0) {
                OnInventoryUpdated.Broadcast();
                return true;
            }
        }
    }
    OnInventoryUpdated.Broadcast();
    return Amount <= 0;
}

// DropItem implementation
bool UInventoryComponent::DropItem(int32 SlotIndex, int32 AmountToDrop)
{

    if (!InventorySlots.IsValidIndex(SlotIndex)) {
        UE_LOG(LogTemp, Error, TEXT("DROP FAILED: Invalid Index %d"), SlotIndex);
        return false;
    };

    if (InventorySlots[SlotIndex].Quantity < AmountToDrop || AmountToDrop <= 0) {
        UE_LOG(LogTemp, Error, TEXT("DROP FAILED: Not enough quantity. Have: %d, Wanted: %d"), InventorySlots[SlotIndex].Quantity, AmountToDrop);
        return false;
    }
    FItemData ItemToDropData = InventorySlots[SlotIndex].ItemData;

    InventorySlots[SlotIndex].Quantity -= AmountToDrop;

    if (InventorySlots[SlotIndex].Quantity == 0) {
        InventorySlots[SlotIndex].ItemData = FItemData();
    }

    AActor* OwnerActor = GetOwner();

    if (OwnerActor && ItemToDropData.ItemClass) {
        FVector SpawnLocation = OwnerActor->GetActorLocation() + (OwnerActor->GetActorForwardVector() * 150.0f) + FVector(0, 0, 30.0f);
        FRotator SpawnRotation = FRotator::ZeroRotator;

        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

        AActor* DroppedActor = GetWorld()->SpawnActor<AActor>(ItemToDropData.ItemClass, SpawnLocation, SpawnRotation, SpawnParams);

        if (DroppedActor)
        {
            FIntProperty* AmountProp = CastField<FIntProperty>(DroppedActor->GetClass()->FindPropertyByName(TEXT("DroppedAmount")));

            if (AmountProp)
            {
                AmountProp->SetPropertyValue_InContainer(DroppedActor, AmountToDrop);
            }
 
            UStaticMeshComponent* MeshComp = DroppedActor->FindComponentByClass<UStaticMeshComponent>();
            if (MeshComp && MeshComp->IsSimulatingPhysics())
            {
                FVector ThrowDirection = (OwnerActor->GetActorForwardVector() + FVector(0, 0, 0.5f)).GetSafeNormal();
                MeshComp->AddImpulse(ThrowDirection * 500.0f, NAME_None, true);
            }
        }
    }
    OnInventoryUpdated.Broadcast();
    return true;
}
// SwapSlots implementation
void UInventoryComponent::SwapSlots(int32 FromIndex, int32 ToIndex)
{
    if (FromIndex == ToIndex) return;

    if (InventorySlots.IsValidIndex(FromIndex) && InventorySlots.IsValidIndex(ToIndex))
    {
        FInventorySlot& FromSlot = InventorySlots[FromIndex];
        FInventorySlot& ToSlot = InventorySlots[ToIndex];

        if (!ToSlot.ItemData.ItemName.IsNone() && ToSlot.ItemData.ItemName == FromSlot.ItemData.ItemName)
        {
            int32 MaxStack = ToSlot.ItemData.MaxStackSize;
            int32 AvailableSpace = MaxStack - ToSlot.Quantity;

            if (AvailableSpace > 0)
            {
                int32 AmountToTransfer = FMath::Min(FromSlot.Quantity, AvailableSpace);

                ToSlot.Quantity += AmountToTransfer;
                FromSlot.Quantity -= AmountToTransfer;

                if (FromSlot.Quantity <= 0)
                {
                    FromSlot.ItemData = FItemData();
                    FromSlot.Quantity = 0;
                }

                OnInventoryUpdated.Broadcast();
            }
        }
        InventorySlots.Swap(FromIndex, ToIndex);
        OnInventoryUpdated.Broadcast();
    }
}
// DropAllItemsOfSameType implementation
void UInventoryComponent::DropAllItemsOfSameType(FName ItemName) 
{
    int32 TotalAmount = 0;
    FItemData ItemToDropData;
    bool bFound = false;

    for (FInventorySlot& Slot : InventorySlots) {
        if (Slot.ItemData.ItemName == ItemName && Slot.Quantity > 0) {
            if (!bFound) {
                ItemToDropData = Slot.ItemData;
                bFound = true;
            }
            TotalAmount += Slot.Quantity;

            Slot.Quantity = 0;
            Slot.ItemData = FItemData(); 
        }
    }
    if (TotalAmount > 0 && ItemToDropData.ItemClass) {
        AActor* OwnerActor = GetOwner();
        if (OwnerActor) {
            FVector ActorLocation = OwnerActor->GetActorLocation();
            FVector ForwardVector = OwnerActor->GetActorForwardVector();

            FVector SpawnLocation = ActorLocation + (ForwardVector * 100.0f) + FVector(0, 0, 50.0f);

            FActorSpawnParameters SpawnParams;
            SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

            AActor* DroppedActor = GetWorld()->SpawnActor<AActor>(ItemToDropData.ItemClass, SpawnLocation, FRotator::ZeroRotator, SpawnParams);

            if (DroppedActor) {
                FIntProperty* AmountProp = CastField<FIntProperty>(DroppedActor->GetClass()->FindPropertyByName(TEXT("DroppedAmount")));
                if (AmountProp) {
                    AmountProp->SetPropertyValue_InContainer(DroppedActor, TotalAmount);
                }

                UStaticMeshComponent* MeshComp = DroppedActor->FindComponentByClass<UStaticMeshComponent>();
                if (MeshComp && MeshComp->IsSimulatingPhysics()) {
                    MeshComp->AddImpulse(ForwardVector * 300.0f, NAME_None, true);
                }
            }
        }
    }
    OnInventoryUpdated.Broadcast();
}
// SortInventory implementation
void UInventoryComponent::SortInventory()
{
    TMap<FName, int32> ItemTotals;
    TMap<FName, FItemData> ItemDataMap;

    for (const FInventorySlot& Slot : InventorySlots)
    {
        if (!Slot.ItemData.ItemName.IsNone() && Slot.Quantity > 0)
        {
            ItemTotals.FindOrAdd(Slot.ItemData.ItemName) += Slot.Quantity;
            ItemDataMap.FindOrAdd(Slot.ItemData.ItemName) = Slot.ItemData;
        }
    }
    for (int32 i = 0; i < InventorySlots.Num(); i++)
    {
        InventorySlots[i].ItemData = FItemData();
        InventorySlots[i].Quantity = 0;
    }
    TArray<FName> SortedNames;
    ItemTotals.GetKeys(SortedNames);
    SortedNames.Sort([](const FName& A, const FName& B) {
        return A.ToString() < B.ToString();
        });
    int32 CurrentSlotIndex = 0;

    for (FName& Name : SortedNames)
    {
        int32 TotalAmount = ItemTotals[Name];
        FItemData Data = ItemDataMap[Name];
        int32 MaxStack = FMath::Max(1, Data.MaxStackSize);

        while (TotalAmount > 0 && CurrentSlotIndex < InventorySlots.Num())
        {
            int32 AmountInThisSlot = FMath::Min(TotalAmount, MaxStack);

            InventorySlots[CurrentSlotIndex].ItemData = Data;
            InventorySlots[CurrentSlotIndex].Quantity = AmountInThisSlot;

            TotalAmount -= AmountInThisSlot;
            CurrentSlotIndex++;
        }
    }
    OnInventoryUpdated.Broadcast();
}
// UpgradeInventorySize implementation
void UInventoryComponent::UpgradeInventorySize(int32 AdditionalSlots)
{
    MaxInventorySize += AdditionalSlots;
    InventorySlots.SetNum(MaxInventorySize);

    OnInventoryUpdated.Broadcast();
}
// SplitStack implementation
int32 UInventoryComponent::SplitStack(int32 SlotIndex)
{
    if (!InventorySlots.IsValidIndex(SlotIndex)) return 0;

    if (InventorySlots[SlotIndex].Quantity <= 1) return 0;

    int32 FullAmount = InventorySlots[SlotIndex].Quantity;
    int32 KeepAmount = FMath::CeilToInt(FullAmount / 2.0f);
    int32 TakeAmount = FullAmount - KeepAmount;

    int32 EmptySlotIndex = -1;
    for (int32 i = 0; i < InventorySlots.Num(); i++)
    {
        if (InventorySlots[i].ItemData.ItemName.IsNone() || InventorySlots[i].Quantity <= 0)
        {
            EmptySlotIndex = i;
            break;
        }
    }
     
    if (EmptySlotIndex != -1)
    {
        InventorySlots[EmptySlotIndex].ItemData = InventorySlots[SlotIndex].ItemData;
        InventorySlots[EmptySlotIndex].Quantity = TakeAmount;

        InventorySlots[SlotIndex].Quantity = KeepAmount;

        OnInventoryUpdated.Broadcast();
        return TakeAmount;
    }
    return 0;
}