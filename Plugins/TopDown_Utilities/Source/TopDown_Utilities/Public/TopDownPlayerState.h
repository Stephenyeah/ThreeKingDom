// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TopDownPlayerState.generated.h"


class UResourceAttributeSet;
class UAbilitySystemComponent;
struct FOnAttributeChangeData;
/**
 *
 */
UCLASS()
class TOPDOWN_UTILITIES_API ATopDownPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATopDownPlayerState();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Resources")
	void RevertBuildCost(const TMap<FGameplayAttribute, int32>& BuildCost);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resources")
	const class UResourceAttributeSet* ResourceAttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resources")
	UAbilitySystemComponent* AbilitySystemComponent;

	virtual void WoodCountChanged(const FOnAttributeChangeData& Data);
	virtual void StoneCountChanged(const FOnAttributeChangeData& Data);
	virtual void FoodCountChanged(const FOnAttributeChangeData& Data);
	virtual void GoldCountChanged(const FOnAttributeChangeData& Data);

	UFUNCTION(BlueprintCallable, Category = "Resources")
	void OnResourceCountChanged();

	UFUNCTION(BlueprintCallable, Category = "Resources")
	bool ConsumeBuildCost(const TMap<FGameplayAttribute, int32>& BuildCost);

	UFUNCTION(BlueprintCallable, Category = "Resources")
	bool CheckBuildCost(const TMap<FGameplayAttribute, int32>& BuildCost);

};
