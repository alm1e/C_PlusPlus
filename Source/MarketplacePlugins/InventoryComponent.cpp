#include "InventoryComponent.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Net/UnrealNetwork.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	EnsureInventorySize();
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UInventoryComponent, InventorySlots);
	DOREPLIFETIME(UInventoryComponent, MaxInventorySize);
}

//Request
void UInventoryComponent::OnRep_InventorySlots()
{
	BroadcastInventoryUpdated();
}

void UInventoryComponent::BroadcastInventoryUpdated()
{
	OnInventoryUpdated.Broadcast();
}

void UInventoryComponent::EnsureInventorySize()
{
	if (InventorySlots.Num() != MaxInventorySize)
	{
		InventorySlots.SetNum(MaxInventorySize);
	}
}

void UInventoryComponent::RequestDropItem(int32 SlotIndex, int32 AmountToDrop)
{
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		DropItem_Internal(SlotIndex, AmountToDrop);
	}
	else
	{
		ServerDropItem(SlotIndex, AmountToDrop);
	}
}

void UInventoryComponent::RequestSwapSlots(int32 FromIndex, int32 ToIndex)
{
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		SwapSlots_Internal(FromIndex, ToIndex);
	}
	else
	{
		ServerSwapSlots(FromIndex, ToIndex);
	}
}

void UInventoryComponent::RequestDropAllItemsOfSameType(FName ItemName)
{
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		DropAllItemsOfSameType_Internal(ItemName);
	}
	else
	{
		ServerDropAllItemsOfSameType(ItemName);
	}
}

void UInventoryComponent::RequestSortInventory()
{
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		SortInventory_Internal();
	}
	else
	{
		ServerSortInventory();
	}
}

void UInventoryComponent::RequestUpgradeInventorySize(int32 AdditionalSlots)
{
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		UpgradeInventorySize_Internal(AdditionalSlots);
	}
	else
	{
		ServerUpgradeInventorySize(AdditionalSlots);
	}
}

void UInventoryComponent::RequestSplitStack(int32 SlotIndex)
{
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		SplitStack_Internal(SlotIndex);
	}
	else
	{
		ServerSplitStack(SlotIndex);
	}
}

void UInventoryComponent::RequestAddItem(FItemData NewItem, int32 Amount)
{
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		AddItem(NewItem, Amount);
	}
	else
	{
		ServerAddItem(NewItem, Amount);
	}
}


// Server
void UInventoryComponent::ServerDropItem_Implementation(int32 SlotIndex, int32 AmountToDrop)
{
	DropItem_Internal(SlotIndex, AmountToDrop);
}

void UInventoryComponent::ServerSwapSlots_Implementation(int32 FromIndex, int32 ToIndex)
{
	SwapSlots_Internal(FromIndex, ToIndex);
}

void UInventoryComponent::ServerDropAllItemsOfSameType_Implementation(FName ItemName)
{
	DropAllItemsOfSameType_Internal(ItemName);
}

void UInventoryComponent::ServerSortInventory_Implementation()
{
	SortInventory_Internal();
}

void UInventoryComponent::ServerUpgradeInventorySize_Implementation(int32 AdditionalSlots)
{
	UpgradeInventorySize_Internal(AdditionalSlots);
}

void UInventoryComponent::ServerSplitStack_Implementation(int32 SlotIndex)
{
	SplitStack_Internal(SlotIndex);
}

void UInventoryComponent::ServerAddItem_Implementation(FItemData NewItem, int32 Amount)
{
	AddItem(NewItem, Amount);
}

// Internal
bool UInventoryComponent::TryAddItem(const FItemData& NewItem, int32 Amount)
{
	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		return false;
	}

	return AddItem(NewItem, Amount);
}

bool UInventoryComponent::AddItem(const FItemData& NewItem, int32 Amount)
{
	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		return false;
	}

	if (Amount <= 0 || NewItem.ItemName.IsNone())
	{
		return false;
	}

	EnsureInventorySize();

	for (FInventorySlot& Slot : InventorySlots)
	{
		if (Slot.Quantity > 0 && Slot.ItemData.ItemName == NewItem.ItemName)
		{
			const int32 AvailableSpace = Slot.ItemData.MaxStackSize - Slot.Quantity;
			if (AvailableSpace > 0)
			{
				const int32 AmountToAdd = FMath::Min(Amount, AvailableSpace);
				Slot.Quantity += AmountToAdd;
				Amount -= AmountToAdd;

				if (Amount <= 0)
				{
					BroadcastInventoryUpdated();
					return true;
				}
			}
		}
	}

	for (FInventorySlot& Slot : InventorySlots)
	{
		if (Slot.Quantity <= 0)
		{
			Slot.ItemData = NewItem;
			const int32 AmountToAdd = FMath::Min(Amount, NewItem.MaxStackSize);
			Slot.Quantity = AmountToAdd;
			Amount -= AmountToAdd;

			if (Amount <= 0)
			{
				BroadcastInventoryUpdated();
				return true;
			}
		}
	}

	BroadcastInventoryUpdated();
	return Amount <= 0;
}

bool UInventoryComponent::DropItem_Internal(int32 SlotIndex, int32 AmountToDrop)
{
	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		return false;
	}

	if (!InventorySlots.IsValidIndex(SlotIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("DropItem_Internal failed: invalid slot %d"), SlotIndex);
		return false;
	}

	FInventorySlot& Slot = InventorySlots[SlotIndex];

	if (AmountToDrop <= 0 || Slot.Quantity < AmountToDrop || Slot.ItemData.ItemName.IsNone())
	{
		UE_LOG(LogTemp, Warning, TEXT("DropItem_Internal failed: invalid quantity"));
		return false;
	}

	const FItemData ItemToDropData = Slot.ItemData;
	Slot.Quantity -= AmountToDrop;

	if (Slot.Quantity <= 0)
	{
		Slot.ItemData = FItemData();
		Slot.Quantity = 0;
	}

	AActor* OwnerActor = GetOwner();
	if (OwnerActor && ItemToDropData.ItemClass)
	{
		const FVector SpawnLocation =
			OwnerActor->GetActorLocation() +
			(OwnerActor->GetActorForwardVector() * 150.0f) +
			FVector(0.0f, 0.0f, 30.0f);

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = OwnerActor;
		SpawnParams.Instigator = Cast<APawn>(OwnerActor);
		SpawnParams.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		AActor* DroppedActor = GetWorld()->SpawnActor<AActor>(
			ItemToDropData.ItemClass,
			SpawnLocation,
			FRotator::ZeroRotator,
			SpawnParams
		);

		if (DroppedActor)
		{
			DroppedActor->SetReplicates(true);

			if (FIntProperty* AmountProp = CastField<FIntProperty>(
				DroppedActor->GetClass()->FindPropertyByName(TEXT("DroppedAmount"))))
			{
				AmountProp->SetPropertyValue_InContainer(DroppedActor, AmountToDrop);
			}

			if (UStaticMeshComponent* MeshComp = DroppedActor->FindComponentByClass<UStaticMeshComponent>())
			{
				if (MeshComp->IsSimulatingPhysics())
				{
					const FVector ThrowDirection =
						(OwnerActor->GetActorForwardVector() + FVector(0.0f, 0.0f, 0.5f)).GetSafeNormal();
					MeshComp->AddImpulse(ThrowDirection * 500.0f, NAME_None, true);
				}
			}
		}
	}

	BroadcastInventoryUpdated();
	return true;
}

void UInventoryComponent::SwapSlots_Internal(int32 FromIndex, int32 ToIndex)
{
	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		return;
	}

	if (FromIndex == ToIndex)
	{
		return;
	}

	if (!InventorySlots.IsValidIndex(FromIndex) || !InventorySlots.IsValidIndex(ToIndex))
	{
		return;
	}

	FInventorySlot& FromSlot = InventorySlots[FromIndex];
	FInventorySlot& ToSlot = InventorySlots[ToIndex];

	if (FromSlot.Quantity <= 0)
	{
		return;
	}

	if (!ToSlot.ItemData.ItemName.IsNone() && ToSlot.ItemData.ItemName == FromSlot.ItemData.ItemName)
	{
		const int32 MaxStack = ToSlot.ItemData.MaxStackSize;
		const int32 AvailableSpace = MaxStack - ToSlot.Quantity;

		if (AvailableSpace > 0)
		{
			const int32 AmountToTransfer = FMath::Min(FromSlot.Quantity, AvailableSpace);
			ToSlot.Quantity += AmountToTransfer;
			FromSlot.Quantity -= AmountToTransfer;

			if (FromSlot.Quantity <= 0)
			{
				FromSlot.ItemData = FItemData();
				FromSlot.Quantity = 0;
			}

			BroadcastInventoryUpdated();
			return;
		}
	}

	InventorySlots.Swap(FromIndex, ToIndex);
	BroadcastInventoryUpdated();
}

void UInventoryComponent::DropAllItemsOfSameType_Internal(FName ItemName)
{
	if (!GetOwner() || !GetOwner()->HasAuthority() || ItemName.IsNone())
	{
		return;
	}

	int32 TotalAmount = 0;
	FItemData ItemToDropData;
	bool bFound = false;

	for (FInventorySlot& Slot : InventorySlots)
	{
		if (Slot.ItemData.ItemName == ItemName && Slot.Quantity > 0)
		{
			if (!bFound)
			{
				ItemToDropData = Slot.ItemData;
				bFound = true;
			}

			TotalAmount += Slot.Quantity;
			Slot.Quantity = 0;
			Slot.ItemData = FItemData();
		}
	}

	if (TotalAmount > 0 && ItemToDropData.ItemClass)
	{
		AActor* OwnerActor = GetOwner();
		if (OwnerActor)
		{
			const FVector SpawnLocation =
				OwnerActor->GetActorLocation() +
				(OwnerActor->GetActorForwardVector() * 100.0f) +
				FVector(0.0f, 0.0f, 50.0f);

			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = OwnerActor;
			SpawnParams.Instigator = Cast<APawn>(OwnerActor);
			SpawnParams.SpawnCollisionHandlingOverride =
				ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			AActor* DroppedActor = GetWorld()->SpawnActor<AActor>(
				ItemToDropData.ItemClass,
				SpawnLocation,
				FRotator::ZeroRotator,
				SpawnParams
			);

			if (DroppedActor)
			{
				DroppedActor->SetReplicates(true);

				if (FIntProperty* AmountProp = CastField<FIntProperty>(
					DroppedActor->GetClass()->FindPropertyByName(TEXT("DroppedAmount"))))
				{
					AmountProp->SetPropertyValue_InContainer(DroppedActor, TotalAmount);
				}

				if (UStaticMeshComponent* MeshComp = DroppedActor->FindComponentByClass<UStaticMeshComponent>())
				{
					if (MeshComp->IsSimulatingPhysics())
					{
						MeshComp->AddImpulse(OwnerActor->GetActorForwardVector() * 300.0f, NAME_None, true);
					}
				}
			}
		}
	}

	BroadcastInventoryUpdated();
}

void UInventoryComponent::SortInventory_Internal()
{
	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		return;
	}

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

	for (FInventorySlot& Slot : InventorySlots)
	{
		Slot.ItemData = FItemData();
		Slot.Quantity = 0;
	}

	TArray<FName> SortedNames;
	ItemTotals.GetKeys(SortedNames);
	SortedNames.Sort([](const FName& A, const FName& B)
		{
			return A.ToString() < B.ToString();
		});

	int32 CurrentSlotIndex = 0;

	for (FName& Name : SortedNames)
	{
		int32 TotalAmount = ItemTotals[Name];
		const FItemData Data = ItemDataMap[Name];
		const int32 MaxStack = FMath::Max(1, Data.MaxStackSize);

		while (TotalAmount > 0 && CurrentSlotIndex < InventorySlots.Num())
		{
			const int32 AmountInThisSlot = FMath::Min(TotalAmount, MaxStack);
			InventorySlots[CurrentSlotIndex].ItemData = Data;
			InventorySlots[CurrentSlotIndex].Quantity = AmountInThisSlot;
			TotalAmount -= AmountInThisSlot;
			CurrentSlotIndex++;
		}
	}

	BroadcastInventoryUpdated();
}

void UInventoryComponent::UpgradeInventorySize_Internal(int32 AdditionalSlots)
{
	if (!GetOwner() || !GetOwner()->HasAuthority() || AdditionalSlots <= 0)
	{
		return;
	}

	MaxInventorySize += AdditionalSlots;
	InventorySlots.SetNum(MaxInventorySize);
	BroadcastInventoryUpdated();
}

int32 UInventoryComponent::SplitStack_Internal(int32 SlotIndex)
{
	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		return 0;
	}

	if (!InventorySlots.IsValidIndex(SlotIndex))
	{
		return 0;
	}

	if (InventorySlots[SlotIndex].Quantity <= 1)
	{
		return 0;
	}

	const int32 FullAmount = InventorySlots[SlotIndex].Quantity;
	const int32 KeepAmount = FMath::CeilToInt(FullAmount / 2.0f);
	const int32 TakeAmount = FullAmount - KeepAmount;

	int32 EmptySlotIndex = INDEX_NONE;
	for (int32 i = 0; i < InventorySlots.Num(); ++i)
	{
		if (InventorySlots[i].Quantity <= 0 || InventorySlots[i].ItemData.ItemName.IsNone())
		{
			EmptySlotIndex = i;
			break;
		}
	}

	if (EmptySlotIndex == INDEX_NONE)
	{
		return 0;
	}

	InventorySlots[EmptySlotIndex].ItemData = InventorySlots[SlotIndex].ItemData;
	InventorySlots[EmptySlotIndex].Quantity = TakeAmount;
	InventorySlots[SlotIndex].Quantity = KeepAmount;

	BroadcastInventoryUpdated();
	return TakeAmount;
}

