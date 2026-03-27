// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	CurrentStamina = MaxStamina;

	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);
	OnStaminaChanged.Broadcast(CurrentStamina, MaxStamina);
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (bCanRegenerate && CurrentHealth < MaxHealth && CurrentHealth > 0.0f) { // HP Regeneration
		CurrentHealth += RegenRate * DeltaTime;
		if (CurrentHealth > MaxHealth) {
			CurrentHealth = MaxHealth;
		}
		OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);
	}
	
	if (CurrentStamina < MaxStamina && CurrentHealth > 0.0f) { //Stamina Regeneration
		CurrentStamina += StaminaRegenRate * DeltaTime;
		CurrentStamina = FMath::Clamp(CurrentStamina, 0.0f, MaxStamina);
		OnStaminaChanged.Broadcast(CurrentStamina, MaxStamina);
	}
}

void UHealthComponent::TakeDamage(float DamageAmount) { //TakeDamage
	if (DamageAmount <= 0.0f || CurrentHealth <= 0.0f) return;
	CurrentHealth -= DamageAmount;
	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);

	if (CurrentHealth <= 0.0f) {
		CurrentHealth = 0.0f;
		UE_LOG(LogTemp, Warning, TEXT("Character is dead!"));

		CurrentStamina = 0.0f;
		OnStaminaChanged.Broadcast(CurrentStamina, MaxStamina);

		OnDeath.Broadcast();
	}
}

void UHealthComponent::UseStamina(float Amount) { //UseStamina
	if (CurrentHealth <= 0.0f || CurrentStamina < Amount) return; 

	CurrentStamina -= Amount;
	OnStaminaChanged.Broadcast(CurrentStamina, MaxStamina);
	
}