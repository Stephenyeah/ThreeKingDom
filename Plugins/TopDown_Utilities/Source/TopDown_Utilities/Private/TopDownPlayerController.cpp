// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownPlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h" 
#include "InputActionValue.h"
#include <TKBasePawn.h>


// Sets default values
ATopDownPlayerController::ATopDownPlayerController() 
{
	
	bShowMouseCursor = true; // Show the mouse cursor
}

// Called to bind functionality to input
void ATopDownPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent(); // Call the base class SetupInputComponent
	
	if (!DefaultInputMappingContext)  // Check if the DefaultInputMappingContext is valid
	{
		return;
	}

	// Add Input Mapping Context
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()); // Get the local player subsystem
	
	if (Subsystem)
	{
		Subsystem->AddMappingContext(DefaultInputMappingContext, 0);  // Add the input mapping context with priority 0
		UE_LOG(LogTemp, Display, TEXT("Input mapping context added.")); 
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Bind the MoveAction to the Move function
		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Completed, this, &ATopDownPlayerController::Select);


	}
}


void ATopDownPlayerController::Select(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("Select action!"));

	FHitResult HitResult;

	GetHitResultUnderCursor(ECollisionChannel::ECC_Camera, false, HitResult);
	
	AActor* SelectedActor = HitResult.GetActor();

	if (SelectedActor)
	{
		UE_LOG(LogTemp, Display, TEXT("Selected Actor: %s"), *SelectedActor->GetName());

		// Deselect the previously selected pawn
		if(SelectedPawn)
		{
			SelectedPawn->SelectActor(false); 
		}

		SelectedPawn = Cast<ATKBasePawn>(SelectedActor); // Cast the selected actor to ATKBasePawn

		// SelectActor on the selected pawn
		if (SelectedPawn)
		{
			SelectedPawn->SelectActor(true); 
		}
	
	}
}
