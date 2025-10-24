// Fill out your copyright notice in the Description page of Project Settings.


#include "TKBasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
ATKBasePawn::ATKBasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create Capsule
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	RootComponent = CapsuleComponent;
	CapsuleComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	//Create Skeletal mesh
	SkeletalMesh =  CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(RootComponent);

	//Create floating pawn movement
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));

	//Create selection indicator
	SelectIndicator = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SelectIndicator"));
	SelectIndicator->SetupAttachment(RootComponent);
	SelectIndicator->SetHiddenInGame(true);
	SelectIndicator->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ATKBasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATKBasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATKBasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Select or Deselect the actor
void ATKBasePawn::SelectActor(const bool Select)
{
	SelectIndicator->SetHiddenInGame(!Select);
}



