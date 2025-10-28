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

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent); // Cast the InputComponent to UEnhancedInputComponent

	if (EnhancedInputComponent)
	{
		// Bind the MoveAction to the Move function
		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Completed, this, &ATopDownPlayerController::Select);

		// Bind the CommandAction to the CommandSelectedActor function
		EnhancedInputComponent->BindAction(CommandAction, ETriggerEvent::Completed, this, &ATopDownPlayerController::CommandSelectedActor);

	}
}

// Select action implementation
void ATopDownPlayerController::Select(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("Select action!"));

	FHitResult HitResult;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Camera, false, HitResult);

	//Deselect previous selected actor via interface
	if (SelectedActor)
	{
		if (SelectedActor->GetClass()->ImplementsInterface(USelectableInterface::StaticClass()))
		{
			ISelectableInterface::Execute_SelectActor(SelectedActor, false);
		}
	}

	SelectedActor = HitResult.GetActor();

	if (SelectedActor)
	{
		UE_LOG(LogTemp, Display, TEXT("Selected Actor: %s"), *SelectedActor->GetName());

		//select new actor via interface
		if (SelectedActor -> GetClass() -> ImplementsInterface(USelectableInterface::StaticClass()))
		{
			ISelectableInterface::Execute_SelectActor(SelectedActor, true);
		}
	
	}
}

// Command action implementation
void ATopDownPlayerController::CommandSelectedActor(const FInputActionValue& Value)
{
	if (SelectedActor)
	{
		UE_LOG(LogTemp, Display, TEXT("Command action on Selected Actor: %s"), *SelectedActor->GetName());

		if(SelectedActor->GetClass()->ImplementsInterface(UNavigableInterface::StaticClass()))
		{
			FHitResult HitResult;
			GetHitResultUnderCursor(ECollisionChannel::ECC_Camera, false, HitResult);

			if (HitResult.bBlockingHit)
			{
				INavigableInterface::Execute_MoveToLocation(SelectedActor, HitResult.Location);
			}
			
		
		}
	}
}
