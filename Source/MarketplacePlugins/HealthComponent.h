// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAttributeChangedSignature, float, CurrentValue, float, MaxValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStaminaChangedSignature, float, CurrentStamina, float, MaxStamina);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MARKETPLACEPLUGINS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health System")//HP
		float MaxHealth = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health System")
		float CurrentHealth;
	UPROPERTY(BlueprintAssignable, Category="Health System")//Death
		FOnDeathSignature OnDeath;
	UPROPERTY(BlueprintAssignable, Category="Health System")// Optimization for Tick UI
		FOnAttributeChangedSignature OnHealthChanged;
	UFUNCTION(BlueprintCallable, Category = "Health System") // TakeDamage
		void TakeDamage(float DamageAmount);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health System") // HP Regeneration
		bool bCanRegenerate = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health System")
		float RegenRate = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stamina")//Stamina
		float MaxStamina = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stamina")
		float CurrentStamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")//Stamina Regeneration
		float StaminaRegenRate = 15.0f;
	UPROPERTY(BlueprintAssignable, Category = "Stamina")// Optimization for Tick UI
		FOnStaminaChangedSignature OnStaminaChanged;
	UFUNCTION(BlueprintCallable, Category="Stamina")
		void UseStamina(float Amount);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
