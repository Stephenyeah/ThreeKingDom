// Fill out your copyright notice in the Description page of Project Settings.

#include "TKCombatComponent.h"
#include "TKActorComponent.h"
#include "NavigableInterface.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"


// constructor
UTKCombatComponent::UTKCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Initialize
void UTKCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	// Get the owner's stats component
	AActor* Owner = GetOwner();
	if (Owner)
	{
		ActorStatsComponent = Owner->FindComponentByClass<UTKActorComponent>();
		if (!ActorStatsComponent)
		{
			UE_LOG(LogTemp, Warning, TEXT("[%s] CombatComponent: Missing ActorStatsComponent!"), *Owner->GetName());
		}
	}
}



// Execute attack command
void UTKCombatComponent::PerformAttack(AActor* Target)
{
	if (!ActorStatsComponent || !Target)
		return;

	AActor* Owner = GetOwner();
	if (!Owner) return;

	// 如果目标已死亡或无效，则停止攻击
	if (UTKActorComponent* TargetStats = Target->FindComponentByClass<UTKActorComponent>())
	{
		if (TargetStats->IsDead())
		{
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle_CheckDistance);
			UE_LOG(LogTemp, Display, TEXT("[%s] Stopped attacking — target dead."), *Owner->GetName());
			return;
		}
	}

	// 冷却中不攻击
	if (IsInCooldown())
		return;

	const float AttackRange = ActorStatsComponent->GetAttackRange();
	const float Distance = FVector::Dist(Target->GetActorLocation(), Owner->GetActorLocation());

	// --- 在攻击范围内 ---
	if (Distance <= AttackRange)
	{
		// 停止移动（如果有导航接口）
		if (Owner->GetClass()->ImplementsInterface(UNavigableInterface::StaticClass()))
		{
			INavigableInterface::Execute_StopMovement(Owner);
		}

		// 面向敌人
		const FVector Direction = (Target->GetActorLocation() - Owner->GetActorLocation()).GetSafeNormal();
		Owner->SetActorRotation(Direction.Rotation());

		// 执行攻击
		CurrentTarget = Target;
		LastAttackTime = GetWorld()->GetTimeSeconds();

		UE_LOG(LogTemp, Display, TEXT("[%s] Attacking target: %s"), *Owner->GetName(), *Target->GetName());
		ApplyDamage();

		AttackState = EAttackState::Cooldown;

		// 持续攻击循环
		const float AttackInterval = GetAttackInterval();
		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle_CheckDistance,
			[this]()
			{
				if (IsValid(CurrentTarget) && !IsInCooldown())
				{
					PerformAttack(CurrentTarget);
				}
			},
			AttackInterval, false // false = 单次触发后重新设定（防止叠加计时器）
		);

		return;
	}

	// --- 不在范围内：靠近目标 ---
	if (Owner->GetClass()->ImplementsInterface(UNavigableInterface::StaticClass()))
	{
		FVector Direction = (Target->GetActorLocation() - Owner->GetActorLocation()).GetSafeNormal();
		FVector MoveTarget = Target->GetActorLocation() - Direction * (AttackRange * 0.5f);

		INavigableInterface::Execute_MoveToLocation(Owner, MoveTarget);

		UE_LOG(LogTemp, Display, TEXT("[%s] Moving closer to target... Distance: %.1f, Range: %.1f"),
			*Owner->GetName(), Distance, AttackRange);

		// 重复检测距离，直到进入射程
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_CheckDistance);
		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle_CheckDistance,
			[this, Target]()
			{
				if (!IsValid(Target) || !IsValid(GetOwner())) return;

				const float NewDist = FVector::Dist(Target->GetActorLocation(), GetOwner()->GetActorLocation());
				if (NewDist <= ActorStatsComponent->GetAttackRange())
				{
					GetWorld()->GetTimerManager().ClearTimer(TimerHandle_CheckDistance);
					PerformAttack(Target);
				}
			},
			0.3f, true);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("[%s] Target out of range and cannot move (no NavigableInterface)."),
			*Owner->GetName());
	}
}






// Apply damage
void UTKCombatComponent::ApplyDamage()
{
	if (!ActorStatsComponent || !CurrentTarget)
		return;

	float AttackPower = ActorStatsComponent->GetAttackPower();

	// 目标的属性组件
	if (UTKActorComponent* TargetStats = CurrentTarget->FindComponentByClass<UTKActorComponent>())
	{
		TargetStats->TakeDamage(AttackPower);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] Target has no ActorStatsComponent, cannot apply damage."), *CurrentTarget->GetName());
	}

	// 完成后回到 Idle
	AttackState = EAttackState::Idle;
}




// Check if in cooldown
bool UTKCombatComponent::IsInCooldown() const
{
	if (!ActorStatsComponent) return false;

	float AttackInterval = GetAttackInterval();
	return (GetWorld()->GetTimeSeconds() - LastAttackTime) < AttackInterval;
}

// calculate attack interval
float UTKCombatComponent::GetAttackInterval() const
{
	return (ActorStatsComponent) ? (1.0f / ActorStatsComponent->GetAttackSpeed()) : 1.0f;
}

// Check if target is valid and within attack range
bool UTKCombatComponent::IsTargetValid(AActor* Target) const
{
	if (!Target || !ActorStatsComponent)
		return false;

	const float Range = ActorStatsComponent->GetAttackRange();
	const float Distance = FVector::Dist(Target->GetActorLocation(), GetOwner()->GetActorLocation());
	return Distance <= Range;
}
