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
		EnhancedInputComponent->BindAction(CommandAction, ETriggerEvent::Completed, this, &ATopDownPlayerController::CommandSelectedActors);

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

// Finalize selection rectangle and select actors
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

// Select multiple actors within the selection rectangle
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

		SelectedActors.Empty(); // Clear SelectedActors array

		//Select New Actors
		TArray<AActor*> AllSelectedActors = TopDownHUD->GetSelectedActors();


		for (AActor* SomeActor : AllSelectedActors)
		{
			if (SomeActor)
			{
				//UE_LOG(LogTemp, Warning, TEXT("Selected Pawn: %s"), *SomeActor->GetName());
				if (SomeActor->GetClass()->ImplementsInterface(USelectableInterface::StaticClass()))
				{
					ISelectableInterface::Execute_SelectActor(SomeActor, true);
					SelectedActors.AddUnique(SomeActor); // Add to SelectedActors array filter.
				}

			}
		}
		OnActorsSelected.Broadcast(SelectedActors); // Broadcast the delegate
	}
}

// Command action implementation
void ATopDownPlayerController::CommandSelectedActors(const FInputActionValue& Value)
{
	if (!TopDownHUD || SelectedActors.Num() == 0)
		return;

	FHitResult HitResult;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Camera, false, HitResult);

	if (!HitResult.bBlockingHit)
		return;				//Early return in case of invalid target location



	if (SelectedActors.Num() > 0) // If there are multiple selected actors
	{
		const FVector CenterLocation = HitResult.Location;
		const int32 NumActors = SelectedActors.Num();
		const int32 UnitsPerRow = FMath::CeilToInt(FMath::Sqrt((float)NumActors));
		const float Spacing = 100.f; // Spacing between actors in the formation

		// Loop through each selected actor and calculate its position in the formation
		for (int32 Index = 0; Index < NumActors; Index++)
		{
			AActor* SomeActor = SelectedActors[Index];
			if (!SomeActor || !SomeActor->GetClass()->ImplementsInterface(UNavigableInterface::StaticClass()))
				continue;

			// Calculate row and column based on index
			const int32 Row = Index / UnitsPerRow;
			const int32 Col = Index % UnitsPerRow;

			// Calculate offset from center
			const float HalfSize = (UnitsPerRow - 1) * 0.5f;
			const FVector Offset = FVector(
				(Col - HalfSize) * Spacing,
				(Row - HalfSize) * Spacing,
				0.f
			);

			// Command the actor to move to its position in the formation
			INavigableInterface::Execute_MoveToLocation(SomeActor, CenterLocation + Offset);
		}
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Command action on Selected Actor: %s"), *SelectedActor->GetName());

		if (SelectedActor->GetClass()->ImplementsInterface(UNavigableInterface::StaticClass()))
		{
			INavigableInterface::Execute_MoveToLocation(SelectedActor, HitResult.Location);
		}
	}

}