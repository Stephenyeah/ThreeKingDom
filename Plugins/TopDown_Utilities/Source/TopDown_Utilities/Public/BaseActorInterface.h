// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CommonENUMS.h"
#include "BaseActorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBaseActorInterface : public UInterface
{
	GENERATED_BODY()
};


class ACLMBaseBuilding;

class TOPDOWN_UTILITIES_API IBaseActorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Base Pawn Interface")
	EActorType GetActorType();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Base Pawn Interface")
	TArray<TSubclassOf<ATKBaseBuilding>> GetBuildOptions();
};
