// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SelectableInterface.h"
#include "NavigableInterface.h"
#include "TKBasePawn.generated.h"


class UCapsuleComponent;
class USkeletalMeshComponent;
class UFloatingPawnMovement;


UCLASS()
class TOPDOWN_UTILITIES_API ATKBasePawn : public APawn, public ISelectableInterface, public INavigableInterface
{
	GENERATED_BODY()


public:
	// Sets default values for this pawn's properties
	ATKBasePawn();

private:
	//Capsule Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	//Skeletal Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> SkeletalMesh;


	//Floating Pawn movement component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UFloatingPawnMovement> FloatingPawnMovement;


	//Selection Indicator
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> SelectIndicator;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Navigation
	FVector MoveTargetLocation = FVector::ZeroVector;
	bool bIsMoving = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	UFUNCTION() 
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Select or Deselect the actor
	UFUNCTION() 
	void SelectActorLocal(const bool Select);

	void SelectActor_Implementation(const bool Select) override;

	void MoveToLocation_Implementation(const FVector TargetLocation) override;


};
