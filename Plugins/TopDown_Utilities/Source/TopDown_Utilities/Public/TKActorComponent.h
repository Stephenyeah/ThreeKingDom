// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TKActorComponent.generated.h"

// Declare a delegate for health change events, used to notify listeners when an actor's health changes(sample for health bar refresh)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, float, CurrentHealth, float, MaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWN_UTILITIES_API UTKActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTKActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	// basic attributes
	
	// Maximum Health
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 100.0f;

	// Current Health
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float CurrentHealth = 100.0f;

	// Attack Power
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float AttackPower = 10.0f;

	// Attack Range
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float AttackRange = 50.0f;

	// Attack Speed
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float AttackSpeed = 1.0f;


	// defense attribute (unused yet)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats|Defense", meta = (AllowPrivateAccess = "true"))
	float Defense = 0.0f;

	// Death event, can be bound in Blueprints or C++
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	FOnDeathDelegate OnDeath;

public:	
	// Called every frame
//	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		// ---events---
	// Called when health changes
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHealthChangedSignature OnHealthChanged;

	// --- function constructor ---

	// take damage
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void TakeDamage(float DamageAmount);

	// recover health
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void Heal(float HealAmount);

	// is dead?
	UFUNCTION(BlueprintPure, Category = "Stats")
	bool IsDead() const { return CurrentHealth <= 0.0f; }

	// Get the percentage of health points (for health bars)
	UFUNCTION(BlueprintPure, Category = "Stats")
	float GetHealthPercent() const { return (MaxHealth > 0) ? (CurrentHealth / MaxHealth) : 0.0f; }

	// Getter: Attack Power
	UFUNCTION(BlueprintPure, Category = "Stats")
	float GetAttackPower() const { return AttackPower; }

	// Getter: Attack Range
	UFUNCTION(BlueprintPure, Category = "Stats")
	float GetAttackRange() const { return AttackRange; }

	// Getter: Attack Speed
	UFUNCTION(BlueprintPure, Category = "Stats")
	float GetAttackSpeed() const { return AttackSpeed; }

	// Getter: Defense
	UFUNCTION(BlueprintPure, Category = "Stats")
	float GetDefense() const { return Defense; }



		
};
