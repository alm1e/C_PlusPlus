#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

class UHealthComponent;
class UMeshComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackStartedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackEndedSignature);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MARKETPLACEPLUGINS_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCombatComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float AttackDamage = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float TraceRadius = 12.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float AttackCooldown = 0.7f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool bDebugTrace = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UMeshComponent* WeaponTraceMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	FName WeaponTraceStartSocketName = TEXT("TraceStart");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	FName WeaponTraceEndSocketName = TEXT("TraceEnd");

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	bool bTraceAttackActive = false;

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	bool bIsAttacking = false;

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	bool bCanAttack = true;

	UPROPERTY(BlueprintAssignable, Category = "Combat")
	FOnAttackStartedSignature OnAttackStarted;

	UPROPERTY(BlueprintAssignable, Category = "Combat")
	FOnAttackEndedSignature OnAttackEnded;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void RequestStartAttack();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void PerformAttackHitCheck();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void EndAttack();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void StartAttackTrace();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void StopAttackTrace();

	UFUNCTION(Server, Reliable)
	void ServerStartAttack();

	UFUNCTION(Server, Reliable)
	void ServerPerformAttackHitCheck();

	UFUNCTION(Server, Reliable)
	void ServerEndAttack();

private:
	UPROPERTY()
	TArray<AActor*> HitActorsThisAttack;

	FTimerHandle AttackCooldownTimerHandle;

	void StartAttack_Internal();
	void PerformAttackHitCheck_Internal();
	void EndAttack_Internal();
	void ResetAttackCooldown();

	bool CanAttack() const;
	FVector GetTraceStartLocation() const;
	FVector GetTraceEndLocation() const;
};