// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ControllerPawn.generated.h"  

class UCapsuleComponent;       // 3.Forward declaration of CapsuleComponent
class USpringArmComponent;     // 4.Forward declaration of SpringArmComponent
class UCameraComponent;        // 5.Forward declaration of CameraComponent


UCLASS()
class TOPDOWN_UTILITIES_API AControllerPawn : public APawn
{
	GENERATED_BODY()

private:
	// Capsule Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))  //  1. Make it visible in editor and blueprints, but read-only
		UCapsuleComponent* CapsuleComponent; // 2. Capsule component for collision detection

	// Camera boom positioning the camera behind the character Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))  //  1. Make it visible in editor and blueprints, but read-only
		USpringArmComponent* SpringArm; // 2. Capsule component for collision detection

	// Follow camera Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))  //  1. Make it visible in editor and blueprints, but read-only
		UCameraComponent* Camera; // 2. Capsule component for collision detection

public:
	// Sets default values for this pawn's properties
	AControllerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
