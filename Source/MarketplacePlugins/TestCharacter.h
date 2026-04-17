#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "ItemTypes.h"
#include "TestCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UStaticMeshComponent;
class UUserWidget;
class UInputMappingContext;
class UInputAction;
class UAnimMontage;

class UHealthComponent;
class UCombatComponent;
class UInventoryComponent;

UCLASS()
class MARKETPLACEPLUGINS_API ATestCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATestCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void OnJumped_Implementation() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UHealthComponent* Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCombatComponent* Combat;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UInventoryComponent* Inventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* KatanaMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* IA_Move;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* IA_Look;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* IA_Jump;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* IA_Inventory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* IA_Interact;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* IA_Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	UAnimMontage* HitReactMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float JumpStaminaCost = 20.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> InventoryWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> PickupHintWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> PlayerHealthWidgetClass;

	UFUNCTION(BlueprintNativeEvent, Category = "UI")
	void BP_OpenInventory();
	virtual void BP_OpenInventory_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "UI")
	void BP_CloseInventory();
	virtual void BP_CloseInventory_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "UI")
	bool BP_IsInventoryOpen() const;
	virtual bool BP_IsInventoryOpen_Implementation() const;

	UFUNCTION(BlueprintNativeEvent, Category = "Pickup")
	AActor* BP_GetCurrentPickupItem() const;
	virtual AActor* BP_GetCurrentPickupItem_Implementation() const;

	UFUNCTION(BlueprintNativeEvent, Category = "Pickup")
	void BP_ClearCurrentPickupItem(AActor* ItemRef);
	virtual void BP_ClearCurrentPickupItem_Implementation(AActor* ItemRef);

	UFUNCTION(BlueprintNativeEvent, Category = "Pickup")
	void BP_UpdatePickupHint();
	virtual void BP_UpdatePickupHint_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Pickup")
	void BP_UpdatePickupHighlight();
	virtual void BP_UpdatePickupHighlight_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Pickup")
	void BP_ExtractPickupData(AActor* PickupActor, FItemData& OutItemData, int32& OutAmount, bool& bSuccess);
	virtual void BP_ExtractPickupData_Implementation(AActor* PickupActor, FItemData& OutItemData, int32& OutAmount, bool& bSuccess);

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void StartJump(const FInputActionValue& Value);
	void ToggleInventory(const FInputActionValue& Value);
	void Interact(const FInputActionValue& Value);
	void Attack(const FInputActionValue& Value);

	UFUNCTION()
	void HandleAttackStarted();

	UFUNCTION()
	void HandleAttackEnded();

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerTryPickupItem(AActor* ItemRef);
};