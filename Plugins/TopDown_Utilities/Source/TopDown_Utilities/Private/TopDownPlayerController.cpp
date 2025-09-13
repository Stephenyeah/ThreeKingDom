// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownPlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
ATopDownPlayerController::ATopDownPlayerController() 
{
	
	bShowMouseCursor = true; // Show the mouse cursor
}

// Called to bind functionality to input
void ATopDownPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent(); // Call the base class SetupInputComponent
	
	if (!DefaultInpuMappingContext)  // Check if the DefaultInputMappingContext is valid
	{
		return;
	}

	// Add Input Mapping Context
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()); // Get the local player subsystem
	
	if (Subsystem)
	{
		Subsystem->AddMappingContext(DefaultInpuMappingContext, 0);  // Add the input mapping context with priority 0
		UE_LOG(LogTemp, Display, TEXT("Input mapping context added.")); 
	}

}
