#include "CombatComponent.h"
#include "HealthComponent.h"

#include "GameFramework/Actor.h"
#include "Components/MeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Engine/World.h"

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(false);
}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!WeaponTraceMesh && GetOwner())
	{
		TArray<UMeshComponent*> MeshComponents;
		GetOwner()->GetComponents<UMeshComponent>(MeshComponents);

		for (UMeshComponent* Component : MeshComponents)
		{
			if (Component && Component->GetName() == TEXT("KatanaMesh"))
			{
				WeaponTraceMesh = Component;
				break;
			}
		}
	}
}

void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bTraceAttackActive)
	{
		PerformAttackHitCheck();
	}
}

bool UCombatComponent::CanAttack() const
{
	AActor* OwnerActor = GetOwner();
	if (!OwnerActor)
	{
		return false;
	}

	const UHealthComponent* HealthComponent = OwnerActor->FindComponentByClass<UHealthComponent>();
	if (HealthComponent && HealthComponent->CurrentHealth <= 0.0f)
	{
		return false;
	}

	if (!bCanAttack || bIsAttacking)
	{
		return false;
	}

	return true;
}

void UCombatComponent::RequestStartAttack()
{
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		StartAttack_Internal();
	}
	else
	{
		ServerStartAttack();
	}
}

void UCombatComponent::ServerStartAttack_Implementation()
{
	StartAttack_Internal();
}

void UCombatComponent::StartAttack_Internal()
{
	if (!CanAttack())
	{
		return;
	}

	bIsAttacking = true;
	bCanAttack = false;
	HitActorsThisAttack.Empty();

	OnAttackStarted.Broadcast();

	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(
			AttackCooldownTimerHandle,
			this,
			&UCombatComponent::ResetAttackCooldown,
			AttackCooldown,
			false
		);
	}
}

void UCombatComponent::PerformAttackHitCheck()
{
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		PerformAttackHitCheck_Internal();
	}
	else
	{
		ServerPerformAttackHitCheck();
	}
}

void UCombatComponent::ServerPerformAttackHitCheck_Implementation()
{
	PerformAttackHitCheck_Internal();
}

FVector UCombatComponent::GetTraceStartLocation() const
{
	if (WeaponTraceMesh && WeaponTraceMesh->DoesSocketExist(WeaponTraceStartSocketName))
	{
		return WeaponTraceMesh->GetSocketLocation(WeaponTraceStartSocketName);
	}

	return GetOwner() ? GetOwner()->GetActorLocation() : FVector::ZeroVector;
}

FVector UCombatComponent::GetTraceEndLocation() const
{
	if (WeaponTraceMesh && WeaponTraceMesh->DoesSocketExist(WeaponTraceEndSocketName))
	{
		return WeaponTraceMesh->GetSocketLocation(WeaponTraceEndSocketName);
	}

	return GetOwner() ? GetOwner()->GetActorLocation() : FVector::ZeroVector;
}

void UCombatComponent::PerformAttackHitCheck_Internal()
{
	AActor* OwnerActor = GetOwner();
	if (!OwnerActor || !OwnerActor->HasAuthority())
	{
		return;
	}

	if (!bIsAttacking)
	{
		return;
	}

	const FVector Start = GetTraceStartLocation();
	const FVector End = GetTraceEndLocation();

	TArray<FHitResult> HitResults;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(OwnerActor);

	const bool bHit = UKismetSystemLibrary::SphereTraceMulti(
		this,
		Start,
		End,
		TraceRadius,
		UEngineTypes::ConvertToTraceType(ECC_Pawn),
		false,
		ActorsToIgnore,
		bDebugTrace ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None,
		HitResults,
		true
	);

	if (!bHit)
	{
		return;
	}

	for (const FHitResult& Hit : HitResults)
	{
		AActor* HitActor = Hit.GetActor();
		if (!HitActor || HitActor == OwnerActor)
		{
			continue;
		}

		if (HitActorsThisAttack.Contains(HitActor))
		{
			continue;
		}

		UHealthComponent* TargetHealthComponent = HitActor->FindComponentByClass<UHealthComponent>();
		if (!TargetHealthComponent)
		{
			continue;
		}

		APawn* OwnerPawn = Cast<APawn>(OwnerActor);
		AController* InstigatorController = OwnerPawn ? OwnerPawn->GetController() : nullptr;

		UGameplayStatics::ApplyDamage(
			HitActor,
			AttackDamage,
			InstigatorController,
			OwnerActor,
			UDamageType::StaticClass()
		);
		HitActorsThisAttack.Add(HitActor);
	}
}

void UCombatComponent::EndAttack()
{
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		EndAttack_Internal();
	}
	else
	{
		ServerEndAttack();
	}
}

void UCombatComponent::ServerEndAttack_Implementation()
{
	EndAttack_Internal();
}

void UCombatComponent::EndAttack_Internal()
{
	if (!bIsAttacking)
	{
		return;
	}

	bIsAttacking = false;
	HitActorsThisAttack.Empty();

	OnAttackEnded.Broadcast();
}

void UCombatComponent::ResetAttackCooldown()
{
	bCanAttack = true;
}

void UCombatComponent::StartAttackTrace()
{
	bTraceAttackActive = true;
}

void UCombatComponent::StopAttackTrace()
{
	bTraceAttackActive = false;
}

