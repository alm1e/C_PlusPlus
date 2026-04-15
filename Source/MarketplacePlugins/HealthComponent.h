#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Net/UnrealNetwork.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAttributeChangedSignature, float, CurrentValue, float, MaxValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStaminaChangedSignature, float, CurrentStamina, float, MaxStamina);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MARKETPLACEPLUGINS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health System")
	float MaxHealth = 100.0f;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentHealth, BlueprintReadOnly, Category = "Health System")
	float CurrentHealth = 0.0f;

	UPROPERTY(BlueprintAssignable, Category = "Health System")
	FOnDeathSignature OnDeath;

	UPROPERTY(BlueprintAssignable, Category = "Health System")
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health System")
	bool bCanRegenerate = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health System")
	float RegenRate = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float MaxStamina = 100.0f;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentStamina, BlueprintReadOnly, Category = "Stamina")
	float CurrentStamina = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float StaminaRegenRate = 15.0f;

	UPROPERTY(BlueprintAssignable, Category = "Stamina")
	FOnStaminaChangedSignature OnStaminaChanged;

	UFUNCTION()
	void OnRep_CurrentHealth();

	UFUNCTION()
	void OnRep_CurrentStamina();

	UFUNCTION(BlueprintCallable, Category = "Health System")
	void RequestTakeDamage(float DamageAmount);

	UFUNCTION(BlueprintCallable, Category = "Stamina")
	void RequestUseStamina(float Amount);

	UFUNCTION(Server, Reliable)
	void ServerTakeDamage(float DamageAmount);

	UFUNCTION(Server, Reliable)
	void ServerUseStamina(float Amount);

	void TakeDamage_Internal(float DamageAmount);
	void UseStamina_Internal(float Amount);

private:
	void BroadcastHealthChanged();
	void BroadcastStaminaChanged();
};