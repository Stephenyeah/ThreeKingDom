// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownPlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h" 
#include "InputActionValue.h"
#include <TKBasePawn.h>
#include "TopDownHUD.h"


// Sets default values
ATopDownPlayerController::ATopDownPlayerController() 
{
	
	bShowMouseCursor = true; // Show the mouse cursor
}

void ATopDownPlayerController::BeginPlay()
{
	Super::BeginPlay();

	TopDownHUD = Cast<ATopDownHUD>(GetHUD());
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
		// Bind the SelectAction to the Select function
		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Completed, this, &ATopDownPlayerController::Select);

		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Started, this, &ATopDownPlayerController::SelectStart);
		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Triggered, this, &ATopDownPlayerController::SelectOnGoing);
		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Completed, this, &ATopDownPlayerController::SelectEnd);

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

// Selection rectangle functions
void ATopDownPlayerController::SelectStart(const FInputActionValue& Value)
{
	float MouseX, MouseY;
	GetMousePosition(MouseX, MouseY);
	SelectionStartPosition = FVector2D(MouseX, MouseY);
	UE_LOG(LogTemp, Display, TEXT("Selection started"));
	//UE_LOG(LogTemp, Display, TEXT("Start Position X: %f Y: %f"), MouseX, MouseY);
}

// Update selection rectangle size
void ATopDownPlayerController::SelectOnGoing(const FInputActionValue& Value)
{
	float MouseX, MouseY;
	GetMousePosition(MouseX, MouseY);
	SelectionSize = FVector2D(MouseX - SelectionStartPosition.X, MouseY- SelectionStartPosition.Y);
	UE_LOG(LogTemp, Display, TEXT("Selection ongoing"));
	if (TopDownHUD)
	{
		TopDownHUD->ShowSelectionRect(SelectionStartPosition, SelectionSize);
	}
}

void ATopDownPlayerController::SelectEnd(const FInputActionValue& Value)
{

	UE_LOG(LogTemp, Display, TEXT("Selection end"));
	if(TopDownHUD)
	{
		TopDownHUD->HideSelectionRect();
		FTimerHandle TimerHandleSelectMultipleActors;
		GetWorld()->GetTimerManager().SetTimer(TimerHandleSelectMultipleActors,this,&ATopDownPlayerController::SelectMultipleActors, 0.05f,false);

	}
}

void ATopDownPlayerController::SelectMultipleActors()
{
	if (TopDownHUD)
	{
		// Deselect old selection

		for (AActor* SomeActor : SelectedActors)
		{
			if (SomeActor)
			{
				//UE_LOG(LogTemp, Warning, TEXT("Selected Pawn: %s"), *SomeActor->GetName());
				if (SomeActor->GetClass()->ImplementsInterface(USelectableInterface::StaticClass()))
				{
					ISelectableInterface::Execute_SelectActor(SomeActor, false);
				}

			}
		}

		//Select New Actors
		SelectedActors = TopDownHUD->GetSelectedActors();


		for (AActor* SomeActor : SelectedActors)
		{
			if (SomeActor)
			{
				//UE_LOG(LogTemp, Warning, TEXT("Selected Pawn: %s"), *SomeActor->GetName());
				if (SomeActor->GetClass()->ImplementsInterface(USelectableInterface::StaticClass()))
				{
					ISelectableInterface::Execute_SelectActor(SomeActor, true);
				}

			}
		}
	}
}
