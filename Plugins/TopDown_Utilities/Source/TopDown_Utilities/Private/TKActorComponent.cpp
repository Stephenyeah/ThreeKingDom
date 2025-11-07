// Fill out your copyright notice in the Description page of Project Settings.


#include "TKActorComponent.h"

// Sets default values for this component's properties
UTKActorComponent::UTKActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...


}


// Called when the game starts
void UTKActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// Initialize Current Health to Max Health at the start
	CurrentHealth = MaxHealth;
}


// Take damage
void UTKActorComponent::TakeDamage(float DamageAmount)
{
	if (DamageAmount <= 0.0f || IsDead())
		return;

	// calculate final damage after defense
	const float FinalDamage = FMath::Max(DamageAmount - Defense, 1.0f);
	CurrentHealth = FMath::Clamp(CurrentHealth - FinalDamage, 0.0f, MaxHealth);

	// boardcast health change event
	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);

	// debug log
	UE_LOG(LogTemp, Display, TEXT("[%s] Took %.1f Damage (After Defense %.1f). HP: %.1f / %.1f"),
		*GetOwner()->GetName(), DamageAmount, FinalDamage, CurrentHealth, MaxHealth);

	if (IsDead())
	{
		UE_LOG(LogTemp, Display, TEXT("[%s] has died."), *GetOwner()->GetName());
		OnDeath.Broadcast(); // It can be bound for destruction, playing animations
	}
}


// recover health
void UTKActorComponent::Heal(float HealAmount)
{
	if (HealAmount <= 0.0f || IsDead())
		return;

	CurrentHealth = FMath::Clamp(CurrentHealth + HealAmount, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);

	UE_LOG(LogTemp, Display, TEXT("[%s] Healed %.1f HP. HP: %.1f / %.1f"),
		*GetOwner()->GetName(), HealAmount, CurrentHealth, MaxHealth);
}




// Called every frame
//void UTKActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}

