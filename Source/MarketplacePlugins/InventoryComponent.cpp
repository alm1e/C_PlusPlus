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

bool UInventoryComponent::AddItem(FItemData NewItem, int32 Amount)
{
    // 1. Пытаемся добавить в уже существующие стаки
    for (FInventorySlot& Slot : InventorySlots)
    {
        if (Slot.ItemData.ItemName == NewItem.ItemName)
        {
            // Проверяем, есть ли еще место в этом стаке
            int32 AvailableSpace = Slot.ItemData.MaxStackSize - Slot.Quantity;
            if (AvailableSpace > 0)
            {
                int32 AmountToAdd = FMath::Min(Amount, AvailableSpace);
                Slot.Quantity += AmountToAdd;
                Amount -= AmountToAdd;

                if (Amount <= 0) {
                    OnInventoryUpdated.Broadcast();
                    return true;
                }// Все предметы успешно разложили
            }
        }
    }
    // 2. Если предметы еще остались ищем пустые ячейки
    for (FInventorySlot& Slot : InventorySlots)
    {
        if (Slot.Quantity == 0) // Ячейка пустая
        {
            Slot.ItemData = NewItem;
            int32 AmountToAdd = FMath::Min(Amount, NewItem.MaxStackSize);
            Slot.Quantity = AmountToAdd;
            Amount -= AmountToAdd;
            if (Amount <= 0) {
                OnInventoryUpdated.Broadcast();
                return true; // Всё разложили
            }
        }
    }
    OnInventoryUpdated.Broadcast();
    // Если мы дошли сюда и Amount > 0, значит инвентарь полностью забит
    return Amount <= 0;
}

bool UInventoryComponent::DropItem(int32 SlotIndex, int32 AmountToDrop)
{
    //Проверка индекса
    if (!InventorySlots.IsValidIndex(SlotIndex)) return false;

    //Проверка есть ли что выбрасывать в ячейке
    if (InventorySlots[SlotIndex].Quantity < AmountToDrop || AmountToDrop <= 0) return false;

    // !!! ВАЖНО: Сначала запоминаем данные предмета (включая его класс) !!!
    FItemData ItemToDropData = InventorySlots[SlotIndex].ItemData;

    //Уменьшаем количество предметов в инвентаре
    InventorySlots[SlotIndex].Quantity -= AmountToDrop;

    // Если предметы закончились то очищаем ячейку от предмета
    if (InventorySlots[SlotIndex].Quantity == 0) {
        InventorySlots[SlotIndex].ItemData = FItemData(); //Сброс до дефолта
    }

    //Спавн предмета в мире перед персонажем 
    AActor* OwnerActor = GetOwner();

    // Проверка на владельца и класс предмета
    if (OwnerActor && ItemToDropData.ItemClass) {
        //Вычисление точки перед игроком (150 единиц вперед и 30 вверх, чтобы не застревал)
        FVector SpawnLocation = OwnerActor->GetActorLocation() + (OwnerActor->GetActorForwardVector() * 150.0f) + FVector(0, 0, 30.0f);
        FRotator SpawnRotation = FRotator::ZeroRotator;

        FActorSpawnParameters SpawnParams;
        //Коллизия если уже есть предмет, то попытается сдвинуть, но заспавнит точно
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

        //  Спавним кубик руды в мире
        AActor* DroppedActor = GetWorld()->SpawnActor<AActor>(ItemToDropData.ItemClass, SpawnLocation, SpawnRotation, SpawnParams);

        if (DroppedActor)
        {
            //  ищем переменную DroppedAmount в созданном блюпринте
            FIntProperty* AmountProp = CastField<FIntProperty>(DroppedActor->GetClass()->FindPropertyByName(TEXT("DroppedAmount")));

            if (AmountProp)
            {
                // Записываем в нее то количество, которое мы РЕАЛЬНО выкинули
                AmountProp->SetPropertyValue_InContainer(DroppedActor, AmountToDrop);
            }

            //  Даем физический пинок актору
            UStaticMeshComponent* MeshComp = DroppedActor->FindComponentByClass<UStaticMeshComponent>();
            if (MeshComp && MeshComp->IsSimulatingPhysics())
            {
                FVector ThrowDirection = (OwnerActor->GetActorForwardVector() + FVector(0, 0, 0.5f)).GetSafeNormal();
                MeshComp->AddImpulse(ThrowDirection * 500.0f, NAME_None, true);
            }
        }
    }
    //Даем знать UI что данные поменялись
    OnInventoryUpdated.Broadcast();

    return true;
}

void UInventoryComponent::SwapSlots(int32 FromIndex, int32 ToIndex)
{
    if (FromIndex == ToIndex) return;

    if (InventorySlots.IsValidIndex(FromIndex) && InventorySlots.IsValidIndex(ToIndex))
    {
        FInventorySlot& FromSlot = InventorySlots[FromIndex];
        FInventorySlot& ToSlot = InventorySlots[ToIndex];

        // Если в целевом слоте такой же предмет
        if (!ToSlot.ItemData.ItemName.IsNone() && ToSlot.ItemData.ItemName == FromSlot.ItemData.ItemName)
        {
            int32 MaxStack = ToSlot.ItemData.MaxStackSize;
            int32 AvailableSpace = MaxStack - ToSlot.Quantity;

            if (AvailableSpace > 0)
            {
                // Вычисляем сколько можем переложить
                int32 AmountToTransfer = FMath::Min(FromSlot.Quantity, AvailableSpace);

                ToSlot.Quantity += AmountToTransfer;
                FromSlot.Quantity -= AmountToTransfer;

                // Если в исходном слоте ничего не осталось полностью очищаем его
                if (FromSlot.Quantity <= 0)
                {
                    FromSlot.ItemData = FItemData();
                    FromSlot.Quantity = 0;
                }

                OnInventoryUpdated.Broadcast();
                return; // Выходим так как мы сделали слияние а не простой свап
            }
        }

        // Если предметы разные или в целевом слоте нет места делаем обычный обмен 
        InventorySlots.Swap(FromIndex, ToIndex);
        OnInventoryUpdated.Broadcast();
    }
}

void UInventoryComponent::DropAllItemsOfSameType(FName ItemName) 
{
    int32 TotalAmount = 0;
    FItemData ItemToDropData;
    bool bFound = false;

    //Считаем общее кол-во слотов и очистка
    for (FInventorySlot& Slot : InventorySlots) {
        if (Slot.ItemData.ItemName == ItemName && Slot.Quantity > 0) {
            if (!bFound) {
                ItemToDropData = Slot.ItemData;
                bFound = true;
            }
            TotalAmount += Slot.Quantity;

            // очищаем слот
            Slot.Quantity = 0;
            Slot.ItemData = FItemData(); // Дефолт
        }
    }
    // Внутри DropAllItemsOfSameType после подсчета TotalAmount
    if (TotalAmount > 0 && ItemToDropData.ItemClass) {
        AActor* OwnerActor = GetOwner();
        if (OwnerActor) {
            // Берем позицию игрока
            FVector ActorLocation = OwnerActor->GetActorLocation();
            FVector ForwardVector = OwnerActor->GetActorForwardVector();

            //  Точка спавна
            FVector SpawnLocation = ActorLocation + (ForwardVector * 100.0f) + FVector(0, 0, 50.0f);

            FActorSpawnParameters SpawnParams;
            SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

            AActor* DroppedActor = GetWorld()->SpawnActor<AActor>(ItemToDropData.ItemClass, SpawnLocation, FRotator::ZeroRotator, SpawnParams);

            if (DroppedActor) {
                // Устанавливает количество
                FIntProperty* AmountProp = CastField<FIntProperty>(DroppedActor->GetClass()->FindPropertyByName(TEXT("DroppedAmount")));
                if (AmountProp) {
                    AmountProp->SetPropertyValue_InContainer(DroppedActor, TotalAmount);
                }

                //  Если  включена физика дать легкий импульс вперед
                UStaticMeshComponent* MeshComp = DroppedActor->FindComponentByClass<UStaticMeshComponent>();
                if (MeshComp && MeshComp->IsSimulatingPhysics()) {
                    // Маленький толчок вперед, чтобы объект не падал прямо под ноги
                    MeshComp->AddImpulse(ForwardVector * 300.0f, NAME_None, true);
                }
            }
        }
    }
    //обновление 
    OnInventoryUpdated.Broadcast();
}

void UInventoryComponent::SortInventory()
{
    // Создаем временную карту, чтобы собрать все предметы одного типа вместе ||  Имя предмета -> Общее количество
    TMap<FName, int32> ItemTotals;
    TMap<FName, FItemData> ItemDataMap;

    for (const FInventorySlot& Slot : InventorySlots)
    {
        if (!Slot.ItemData.ItemName.IsNone() && Slot.Quantity > 0)
        {
            ItemTotals.FindOrAdd(Slot.ItemData.ItemName) += Slot.Quantity;
            // Сохраняем данные предмета (иконку, класс и т.д.)
            ItemDataMap.FindOrAdd(Slot.ItemData.ItemName) = Slot.ItemData;
        }
    }
    // Полностью очищаем инвентарь
    for (int32 i = 0; i < InventorySlots.Num(); i++)
    {
        InventorySlots[i].ItemData = FItemData();
        InventorySlots[i].Quantity = 0;
    }
    // Сортируем имена предметов по алфавиту 
    TArray<FName> SortedNames;
    ItemTotals.GetKeys(SortedNames);
    SortedNames.Sort([](const FName& A, const FName& B) {
        return A.ToString() < B.ToString();
        });
    // Раскладываем предметы обратно по слотам соблюдая MaxStackSize
    int32 CurrentSlotIndex = 0;

    for (FName& Name : SortedNames)
    {
        int32 TotalAmount = ItemTotals[Name];
        FItemData Data = ItemDataMap[Name];
        int32 MaxStack = FMath::Max(1, Data.MaxStackSize); // Защита от 0 в MaxStackSize

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

void UInventoryComponent::UpgradeInventorySize(int32 AdditionalSlots)
{
    MaxInventorySize += AdditionalSlots;
    // SetNum добавит новые пустые элементы 
    InventorySlots.SetNum(MaxInventorySize);

    OnInventoryUpdated.Broadcast();
}

int32 UInventoryComponent::SplitStack(int32 SlotIndex)
{
    // Валидность индекса
    if (!InventorySlots.IsValidIndex(SlotIndex)) return 0;

    // Есть ли что делить?
    if (InventorySlots[SlotIndex].Quantity <= 1) return 0;

    int32 FullAmount = InventorySlots[SlotIndex].Quantity;
    int32 KeepAmount = FMath::CeilToInt(FullAmount / 2.0f);
    int32 TakeAmount = FullAmount - KeepAmount;

    // Ищем пустой слот
    int32 EmptySlotIndex = -1;
    for (int32 i = 0; i < InventorySlots.Num(); i++)
    {
        // Проверяем и имя и количество 
        // Слот пустой если имени нет или количество равно 0
        if (InventorySlots[i].ItemData.ItemName.IsNone() || InventorySlots[i].Quantity <= 0)
        {
            EmptySlotIndex = i;
            break;
        }
    }
     
    if (EmptySlotIndex != -1)
    {
        // Сначала копируем данные предмета в новый слот
        InventorySlots[EmptySlotIndex].ItemData = InventorySlots[SlotIndex].ItemData;
        InventorySlots[EmptySlotIndex].Quantity = TakeAmount;

        // Затем уменьшаем количество в старом
        InventorySlots[SlotIndex].Quantity = KeepAmount;

        OnInventoryUpdated.Broadcast();
        return TakeAmount;
    }
    return 0; // Если дошли сюда значит свободных слотов нет
}