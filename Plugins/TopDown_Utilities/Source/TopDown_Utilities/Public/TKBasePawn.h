// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SelectableInterface.h"
#include "NavigableInterface.h"
#include "CommonENUMS.h"
#include "BaseActorInterface.h"
#include "FactionInterface.h"
#include "TKBasePawn.generated.h"




class UCapsuleComponent;
class USkeletalMeshComponent;
class UFloatingPawnMovement;
class UTKActorComponent;
class UTKCombatComponent;


UCLASS()
class TOPDOWN_UTILITIES_API ATKBasePawn : public APawn, public ISelectableInterface, public INavigableInterface, public IBaseActorInterface, public IFactionInterface
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

	//Pawn Type
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	EActorType ActorType = EActorType::Infantry;

	// Faction ID
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	int32 FactionID = 1;

	//actor Stats Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UTKActorComponent> ActorStatsComponent;

	// Combat Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UTKCombatComponent> CombatComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OrientPawnToMovementDirection();

	// Navigation
	FVector MoveTargetLocation = FVector::ZeroVector;
	bool bMoving = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	float AcceptanceDistance = 20.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	float CharacterTurnSpeed = 5.f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	UFUNCTION() 
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Select or Deselect the actor
	UFUNCTION() 
	void SelectActorLocal(const bool Select);


	// === Combat API ===
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void AttackTarget(AActor* Target);

	UFUNCTION(BlueprintPure, Category = "Combat")
	UTKCombatComponent* GetCombatComponent() const { return CombatComponent; }

	void SelectActor_Implementation(const bool Select) override;

	void MoveToLocation_Implementation(const FVector TargetLocation) override;

	EActorType GetActorType_Implementation() override;

	void SetFaction_Implementation(int32 NewFaction) override;

	int32 GetFaction_Implementation() override;

	

};
