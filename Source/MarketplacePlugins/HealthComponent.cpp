#include "HealthComponent.h"
#include "Net/UnrealNetwork.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner() && GetOwner()->HasAuthority())
	{
		CurrentHealth = MaxHealth;
		CurrentStamina = MaxStamina;
	}

	BroadcastHealthChanged();
	BroadcastStaminaChanged();
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		return;
	}

	if (bCanRegenerate && CurrentHealth > 0.0f && CurrentHealth < MaxHealth)
	{
		CurrentHealth += RegenRate * DeltaTime;
		CurrentHealth = FMath::Clamp(CurrentHealth, 0.0f, MaxHealth);
		BroadcastHealthChanged();
	}

	if (CurrentHealth > 0.0f && CurrentStamina < MaxStamina)
	{
		CurrentStamina += StaminaRegenRate * DeltaTime;
		CurrentStamina = FMath::Clamp(CurrentStamina, 0.0f, MaxStamina);
		BroadcastStaminaChanged();
	}
}

void UHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHealthComponent, CurrentHealth);
	DOREPLIFETIME(UHealthComponent, CurrentStamina);
}

void UHealthComponent::OnRep_CurrentHealth()
{
	BroadcastHealthChanged();

	if (CurrentHealth <= 0.0f)
	{
		OnDeath.Broadcast();
	}
}

void UHealthComponent::OnRep_CurrentStamina()
{
	BroadcastStaminaChanged();
}

void UHealthComponent::BroadcastHealthChanged()
{
	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);
}

void UHealthComponent::BroadcastStaminaChanged()
{
	OnStaminaChanged.Broadcast(CurrentStamina, MaxStamina);
}

void UHealthComponent::RequestTakeDamage(float DamageAmount)
{
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		TakeDamage_Internal(DamageAmount);
	}
	else
	{
		ServerTakeDamage(DamageAmount);
	}
}

void UHealthComponent::RequestUseStamina(float Amount)
{
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		UseStamina_Internal(Amount);
	}
	else
	{
		ServerUseStamina(Amount);
	}
}

void UHealthComponent::ServerTakeDamage_Implementation(float DamageAmount)
{
	TakeDamage_Internal(DamageAmount);
}

void UHealthComponent::ServerUseStamina_Implementation(float Amount)
{
	UseStamina_Internal(Amount);
}

void UHealthComponent::TakeDamage_Internal(float DamageAmount)
{
	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		return;
	}

	if (DamageAmount <= 0.0f || CurrentHealth <= 0.0f)
	{
		return;
	}

	CurrentHealth -= DamageAmount;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.0f, MaxHealth);
	BroadcastHealthChanged();

	if (CurrentHealth <= 0.0f)
	{
		CurrentStamina = 0.0f;
		BroadcastStaminaChanged();
		OnDeath.Broadcast();
	}
}

void UHealthComponent::UseStamina_Internal(float Amount)
{
	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		return;
	}

	if (Amount <= 0.0f || CurrentHealth <= 0.0f || CurrentStamina < Amount)
	{
		return;
	}

	CurrentStamina -= Amount;
	CurrentStamina = FMath::Clamp(CurrentStamina, 0.0f, MaxStamina);
	BroadcastStaminaChanged();
}