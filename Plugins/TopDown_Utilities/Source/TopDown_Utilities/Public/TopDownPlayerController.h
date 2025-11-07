// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CommonENUMS.h"
#include "FactionInterface.h"
#include "TopDownPlayerController.generated.h"




/**
 * 
 */

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class ATKBasePawn;
class ATopDownHUD;

// Delegate for when actors are selected
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorsSelectedDelegate, const TArray<AActor*>&, SelectedActors); 

UCLASS()
class TOPDOWN_UTILITIES_API ATopDownPlayerController : public APlayerController, public IFactionInterface
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

	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FOnActorsSelectedDelegate OnActorsSelected;


	// Command Input action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> CommandAction;

	// Currently selected BasePawn Actor
	UPROPERTY()
	TObjectPtr<AActor> SelectedActor;

	UPROPERTY()
	TObjectPtr<ATopDownHUD> TopDownHUD;

	// Faction ID
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	int32 FactionID = 1;

	// Selection box variables
	FVector2D SelectionStartPosition;
	FVector2D SelectionSize;

	TArray<AActor*> SelectedActors;


protected:

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override; // Called to bind functionality to input

	void Select(const FInputActionValue& Value);

	void CommandSelectedActors(const FInputActionValue& Value);
	
	// Selection box functions
	void SelectStart(const FInputActionValue& Value);
	void SelectOnGoing(const FInputActionValue& Value);
	void SelectEnd(const FInputActionValue& Value);
	void SelectMultipleActors();

	void SetFaction_Implementation(int32 NewFaction) override;

	int32 GetFaction_Implementation() override;
};



