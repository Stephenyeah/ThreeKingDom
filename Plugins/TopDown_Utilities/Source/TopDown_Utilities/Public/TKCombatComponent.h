// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NavigableInterface.h"
#include "TKCombatComponent.generated.h"

// Attack state enumeration
UENUM(BlueprintType)
enum class EAttackState : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Attacking UMETA(DisplayName = "Attacking"),
	Cooldown UMETA(DisplayName = "Cooldown")
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOPDOWN_UTILITIES_API UTKCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTKCombatComponent();

protected:
	virtual void BeginPlay() override;

private:
	// --- Fight stats ---
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	EAttackState AttackState = EAttackState::Idle;

	// Last attack timestamp
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float LastAttackTime = 0.f;

	// Attack target
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AActor> CurrentTarget = nullptr;

	// Owner's stats component
	UPROPERTY()
	TObjectPtr<class UTKActorComponent> ActorStatsComponent;

	// Timer handle for distance checking
	FTimerHandle TimerHandle_CheckDistance;

public:
	// --- Attack logic ---

	// Execute attack command (can be called from Controller)
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void PerformAttack(AActor* Target);

	// Apply damage (usually called in attack animation's Notify)
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ApplyDamage();

	// Is in attack cooldown
	UFUNCTION(BlueprintPure, Category = "Combat")
	bool IsInCooldown() const;

private:
	// Check if the target is valid and within attack range
	bool IsTargetValid(AActor* Target) const;

	// Calculate attack interval
	float GetAttackInterval() const;
};
