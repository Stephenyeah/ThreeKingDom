// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownPlayerState.h"
#include "ResourceAttributeSet.h"
#include "ResourceData.h"
#include "AbilitySystemComponent.h"
//#include "GameFramework/GameplayMessageSubsystem.h"

ATopDownPlayerState::ATopDownPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	ResourceAttributeSet = CreateDefaultSubobject<UResourceAttributeSet>(TEXT("ResourceAttributeSet"));

	// Bind the attribute change events
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ResourceAttributeSet->GetWoodAttribute()).AddUObject(this, &ATopDownPlayerState::WoodCountChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ResourceAttributeSet->GetStoneAttribute()).AddUObject(this, &ATopDownPlayerState::StoneCountChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ResourceAttributeSet->GetFoodAttribute()).AddUObject(this, &ATopDownPlayerState::FoodCountChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ResourceAttributeSet->GetGoldAttribute()).AddUObject(this, &ATopDownPlayerState::GoldCountChanged);
	}
}

void ATopDownPlayerState::BeginPlay()
{
	OnResourceCountChanged();
}

void ATopDownPlayerState::WoodCountChanged(const FOnAttributeChangeData& Data)
{
	OnResourceCountChanged();
}
void ATopDownPlayerState::StoneCountChanged(const FOnAttributeChangeData& Data)
{
	OnResourceCountChanged();
}
void ATopDownPlayerState::FoodCountChanged(const FOnAttributeChangeData& Data)
{
	OnResourceCountChanged();
}
void ATopDownPlayerState::GoldCountChanged(const FOnAttributeChangeData& Data)
{
	OnResourceCountChanged();
}


void ATopDownPlayerState::OnResourceCountChanged()
{
	UE_LOG(LogTemp, Warning, TEXT("Resource count changed!"));

	// Message tag for resources updated
	FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Resources.Updated"));

	//// Create a message to broadcast
	//FResourceMessage ResourceMessage;
	//TArray<FGameplayAttribute>& AllResourceAttributes = ResourceMessage.ResourceAttributes;
	//AbilitySystemComponent->GetAllAttributes(AllResourceAttributes);

	//// Broadcast the message
	//UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	//MessageSubsystem.BroadcastMessage<FResourceMessage>(MessageTag, ResourceMessage);


}

bool ATopDownPlayerState::ConsumeBuildCost(const TMap<FGameplayAttribute, int32>& BuildCost)
{
	if (!CheckBuildCost(BuildCost))
	{
		return false;
	}

	for (const auto& Cost : BuildCost)
	{
		FGameplayAttribute Attribute = Cost.Key;
		int32 RequiredAmount = Cost.Value;

		// Deduct the cost from the player's resources
		AbilitySystemComponent->SetNumericAttributeBase(Attribute, AbilitySystemComponent->GetNumericAttribute(Attribute) - RequiredAmount);
	}

	OnResourceCountChanged();
	return true;
}

bool ATopDownPlayerState::CheckBuildCost(const TMap<FGameplayAttribute, int32>& BuildCost)
{

	for (const auto& Cost : BuildCost)
	{
		FGameplayAttribute Attribute = Cost.Key;
		int32 RequiredAmount = Cost.Value;
		// Check if the player has enough resources
		float CurrentValue = AbilitySystemComponent->GetNumericAttribute(Attribute);
		if (CurrentValue < RequiredAmount)
		{
			// Not enough resources
			return false;
		}
	}

	return true;
}

void ATopDownPlayerState::RevertBuildCost(const TMap<FGameplayAttribute, int32>& BuildCost)
{
	for (const auto& Cost : BuildCost)
	{
		FGameplayAttribute Attribute = Cost.Key;
		int32 RequiredAmount = Cost.Value;
		// Add the cost back to the player's resources
		AbilitySystemComponent->SetNumericAttributeBase(Attribute, AbilitySystemComponent->GetNumericAttribute(Attribute) + RequiredAmount);
	}
	OnResourceCountChanged();
}
