// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "NavigableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UNavigableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TOPDOWN_UTILITIES_API INavigableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Navigable Interface")
	void MoveToLocation(const FVector TargetLocation);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Navigable Interface")
	void StopMovement();
};
