// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ControllerPawn.generated.h" 


class UCapsuleComponent;       // 3.Forward declaration of CapsuleComponent
class USpringArmComponent;     // 4.Forward declaration of SpringArmComponent
class UCameraComponent;        // 5.Forward declaration of CameraComponent
class UInputAction;			   // 6.Forward declaration of InputAction
struct FInputActionValue;      // 7.Forward declaration of FInputActionValue
class UFloatingPawnMovement; // 8.Forward declaration of FloatingPawnMovementComponent

UCLASS()
class TOPDOWN_UTILITIES_API AControllerPawn : public APawn
{
	GENERATED_BODY()

private:
	// Capsule ½ºÄÒ Ì«¿Õ²Õ Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))  
	TObjectPtr<UCapsuleComponent> CapsuleComponent; 

	// Camera boom ÉãÏñÍ·µõ¸Ë positioning the camera behind the character Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))  
	TObjectPtr<USpringArmComponent> SpringArm;

	// Follow camera Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))  
	TObjectPtr<UCameraComponent> Camera;


	// CameraProperties 
	UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float CameraZoomSpeed = 10.f;
	UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float MaxCameraOrthWidth = 2500.f;
	UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float MinCameraOrthWidth = 300.f;


	// Movement Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta =(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	// Zoom Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ZoomAction;

	// FloatingPawnMovementComponent
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UFloatingPawnMovement> FloatingPawnMovement;

public:
	// Sets default values for this pawn's properties
	AControllerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called for movement input
	void Move(const FInputActionValue& Value);

	// Called for Zoom input
	void Zoom(const FInputActionValue& Value);

	void EdgeScrollWithMouse();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
