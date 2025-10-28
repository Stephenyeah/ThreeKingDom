// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TopDownPlayerController.generated.h"

/**
 * 
 */

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class ATKBasePawn;

UCLASS()
class TOPDOWN_UTILITIES_API ATopDownPlayerController : public APlayerController
{
	GENERATED_BODY()


	
public:
	ATopDownPlayerController(); 
	
	//  Input Mapping Context
	UPROPERTY(EditDefaultsOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultInputMappingContext;

private:
	// Select Input action
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> SelectAction;


	// Command Input action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> CommandAction;


	// Currently selected BasePawn Actor
	UPROPERTY()
	TObjectPtr<AActor> SelectedActor;




protected:

	virtual void SetupInputComponent() override; // Called to bind functionality to input

	void Select(const FInputActionValue& Value);

	void CommandSelectedActor(const FInputActionValue& Value);
	
};



