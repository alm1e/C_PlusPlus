#include "TestCharacter.h"

#include "HealthComponent.h"
#include "CombatComponent.h"
#include "InventoryComponent.h"

#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputMappingContext.h"

#include "Blueprint/WidgetBlueprintLibrary.h"

ATestCharacter::ATestCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;
	SetReplicateMovement(true);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 200.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	Combat = CreateDefaultSubobject<UCombatComponent>(TEXT("Combat"));
	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));

	KatanaMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KatanaMesh"));
	KatanaMesh->SetupAttachment(GetMesh(), TEXT("KatanaSocket"));
	KatanaMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	KatanaMesh->SetGenerateOverlapEvents(false);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = true;

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 0.0f, 360.0f);
	GetCharacterMovement()->JumpZVelocity = 420.0f;
	GetCharacterMovement()->AirControl = 0.05f;
}

void ATestCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (Combat)
	{
		Combat->OnAttackStarted.AddDynamic(this, &ATestCharacter::HandleAttackStarted);
		Combat->OnAttackEnded.AddDynamic(this, &ATestCharacter::HandleAttackEnded);
	}
	if (KatanaMesh && GetMesh())
	{
		KatanaMesh->AttachToComponent(
			GetMesh(),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale,
			TEXT("KatanaSocket")
		);
	}

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (IsLocallyControlled())
		{
			if (ULocalPlayer* LocalPlayer = PC->GetLocalPlayer())
			{
				if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
					LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
				{
					if (DefaultMappingContext)
					{
						Subsystem->AddMappingContext(DefaultMappingContext, 0);
					}
				}
			}
		}
	}
}

void ATestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!EnhancedInput)
	{
		return;
	}

	if (IA_Move)
	{
		EnhancedInput->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ATestCharacter::Move);
	}

	if (IA_Look)
	{
		EnhancedInput->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ATestCharacter::Look);
	}

	if (IA_Jump)
	{
		EnhancedInput->BindAction(IA_Jump, ETriggerEvent::Started, this, &ATestCharacter::StartJump);
	}

	if (IA_Inventory)
	{
		EnhancedInput->BindAction(IA_Inventory, ETriggerEvent::Started, this, &ATestCharacter::ToggleInventory);
	}

	if (IA_Interact)
	{
		EnhancedInput->BindAction(IA_Interact, ETriggerEvent::Triggered, this, &ATestCharacter::Interact);
	}

	if (IA_Attack)
	{
		EnhancedInput->BindAction(IA_Attack, ETriggerEvent::Triggered, this, &ATestCharacter::Attack);
	}
}

void ATestCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller == nullptr)
	{
		return;
	}

	AddMovementInput(GetActorForwardVector(), MovementVector.X);
	AddMovementInput(GetActorRightVector(), MovementVector.Y);
}

void ATestCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void ATestCharacter::StartJump(const FInputActionValue& Value)
{
	Jump();
}

void ATestCharacter::OnJumped_Implementation()
{
	Super::OnJumped_Implementation();

	if (GetCharacterMovement() && GetCharacterMovement()->IsFalling())
	{
		if (Health)
		{
			Health->RequestUseStamina(JumpStaminaCost);
		}
	}
}

void ATestCharacter::ToggleInventory(const FInputActionValue& Value)
{
	if (BP_IsInventoryOpen())
	{
		BP_CloseInventory();
	}
	else
	{
		BP_OpenInventory();
	}
}

void ATestCharacter::Interact(const FInputActionValue& Value)
{
	AActor* PickupItem = BP_GetCurrentPickupItem();

	if (!PickupItem)
	{
		return;
	}

	ServerTryPickupItem(PickupItem);
}

void ATestCharacter::Attack(const FInputActionValue& Value)
{
	if (Combat)
	{
		Combat->RequestStartAttack();
	}
}

void ATestCharacter::HandleAttackStarted()
{
	if (AttackMontage)
	{
		PlayAnimMontage(AttackMontage);
	}
}

void ATestCharacter::HandleAttackEnded()
{
}

void ATestCharacter::ServerTryPickupItem_Implementation(AActor* ItemRef)
{
	if (!ItemRef)
	{
		return;
	}

	if (GetDistanceTo(ItemRef) > 200.0f)
	{
		return;
	}

	if (!Inventory)
	{
		return;
	}

	FItemData ItemData;
	int32 Amount = 0;
	bool bExtracted = false;

	BP_ExtractPickupData(ItemRef, ItemData, Amount, bExtracted);

	if (!bExtracted)
	{
		return;
	}

	const bool bAdded = Inventory->TryAddItem(ItemData, Amount);
	if (!bAdded)
	{
		return;
	}

	BP_ClearCurrentPickupItem(ItemRef);

	ItemRef->Destroy();

	BP_UpdatePickupHint();
	BP_UpdatePickupHighlight();
}

void ATestCharacter::BP_OpenInventory_Implementation()
{
}

void ATestCharacter::BP_CloseInventory_Implementation()
{
}

bool ATestCharacter::BP_IsInventoryOpen_Implementation() const
{
	return false;
}

AActor* ATestCharacter::BP_GetCurrentPickupItem_Implementation() const
{
	return nullptr;
}

void ATestCharacter::BP_ClearCurrentPickupItem_Implementation(AActor* ItemRef)
{
}

void ATestCharacter::BP_UpdatePickupHint_Implementation()
{
}

void ATestCharacter::BP_UpdatePickupHighlight_Implementation()
{
}

void ATestCharacter::BP_ExtractPickupData_Implementation(AActor* PickupActor, FItemData& OutItemData, int32& OutAmount, bool& bSuccess)
{
	OutAmount = 0;
	bSuccess = false;
}