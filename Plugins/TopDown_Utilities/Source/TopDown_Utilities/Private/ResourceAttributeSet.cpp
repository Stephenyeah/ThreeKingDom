// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceAttributeSet.h"
#include "Net/UnrealNetwork.h"

void UResourceAttributeSet::OnRep_Wood(const FGameplayAttributeData& OldWood)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UResourceAttributeSet, Wood, OldWood);
}

void UResourceAttributeSet::OnRep_Food(const FGameplayAttributeData& OldFood)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UResourceAttributeSet, Food, OldFood);
}

void UResourceAttributeSet::OnRep_Stone(const FGameplayAttributeData& OldStone)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UResourceAttributeSet, Stone, OldStone);
}

void UResourceAttributeSet::OnRep_Gold(const FGameplayAttributeData& OldGold)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UResourceAttributeSet, Gold, OldGold);
}

void UResourceAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UResourceAttributeSet, Wood, COND_None, REPNOTIFY_Always);
}
