// Fill out your copyright notice in the Description page of Project Settings.


#include "ControllerPawn.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
AControllerPawn::AControllerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Capsule Component and set as root component
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));  
	RootComponent = CapsuleComponent; 

	//Create Spring arm
	SpringArm = CreateDefaultSubobject <USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent); // Attach spring arm to root component

	// Create camera
	Camera = CreateDefaultSubobject <UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName); // Attach camera to end of spring arm
	Camera->SetProjectionMode(ECameraProjectionMode::Orthographic);      // Set camera to orthographic mode

	//create FloatingPawnMovementComponent 
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));

}

// Called when the game starts or when spawned
void AControllerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

//Move Function
void AControllerPawn::Move(const FInputActionValue& Value)
{
	const FVector2D MovementInput = Value.Get<FVector2D>(); // Get the 2D movement vector from the input value
	if (Controller)
	{
		const FRotator Roatation = Controller->GetControlRotation();	// Get the controller's rotation
		const FRotator YawRotation(0, Roatation.Yaw, 0);	// We only care about yaw rotation for movement

		const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); // Get forward direction vector
		const FVector Right   = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); // Get forward direction vector

		AddMovementInput(Right, MovementInput.X);			// Move right/left
		AddMovementInput(Forward, MovementInput.Y);		// Move forward/backward

		//AddMovementInput(GetActorForwardVector(), MovementInput.Y);		// Move forward/backward
	}
}

//Zoom Function
void AControllerPawn::Zoom(const FInputActionValue& Value)
{
	// Get the zoom direction from the input value
	const float ZoomDirection = Value.Get<float>();
	if (Controller != nullptr)
	{
		float DesiredOrthoWidth = Camera->OrthoWidth - ZoomDirection*CameraZoomSpeed;
		DesiredOrthoWidth = FMath::Clamp(DesiredOrthoWidth, MinCameraOrthWidth, MaxCameraOrthWidth);
		Camera->OrthoWidth = DesiredOrthoWidth;
	}
}

void AControllerPawn::EdgeScrollWithMouse()
{	
	TObjectPtr<APlayerController> PlayerController = Cast<APlayerController>(GetController()); // Get the PlayerController
	if (!PlayerController)
		return;

	// Get the mouse position
	float MouseX=0, MouseY=0;

	if(PlayerController->GetMousePosition(MouseX, MouseY))
	{
		
		// Get the viewport size
		FVector2D ViewportSize;
		if (GEngine && GEngine-> GameViewport)
		{
			GEngine->GameViewport->GetViewportSize(ViewportSize); // Get the size of the viewport

			float EdgeThreshold = 10.f;						// Define the edge threshold in pixels
			FVector2D MovementInput = FVector2D::ZeroVector; // Initialize movement input vector
				
			if (MouseX < EdgeThreshold)						// Check if mouse is near the left edge
			{
				UE_LOG(LogTemp, Display, TEXT("Left"));
				MovementInput.X = -1.f;						// Move left
			}
			if (MouseX > ViewportSize.X - EdgeThreshold)		
			{
				UE_LOG(LogTemp, Display, TEXT("Right"));		
				MovementInput.X = 1.f;
			}
			if (MouseY < EdgeThreshold)
			{
				UE_LOG(LogTemp, Display, TEXT("Top"));
				MovementInput.Y = 1.f;
			}
			if (MouseY > ViewportSize.Y - EdgeThreshold)
			{
				UE_LOG(LogTemp, Display, TEXT("Bottom"));
				MovementInput.Y = -1.f;
			}


			if (!MovementInput.IsZero())				// If there is movement input, call the Move function
			{
				Move(FInputActionValue(MovementInput));		// Call Move function with the calculated movement input
			}
		}

	}
}




// Called every frame
void AControllerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	EdgeScrollWithMouse();

}

// Called to bind functionality to input
void AControllerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Bind the MoveAction to the Move function
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AControllerPawn::Move);

		//Bond Zoom Function to Zoom input action
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &AControllerPawn::Zoom);

	}

}

