// Fill out your copyright notice in the Description page of Project Settings.


#include "TKBaseBuilding.h"
#include "Components/BoxComponent.h"

// Sets default values
ATKBaseBuilding::ATKBaseBuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//Create Static Mesh Component
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;


	//Create selection indicator
	SelectedIndicator = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SelectedIndicator"));
	SelectedIndicator->SetupAttachment(RootComponent);		
	SelectedIndicator->SetHiddenInGame(true);
	SelectedIndicator->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ATKBaseBuilding::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATKBaseBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Implement Selectable Interface
void ATKBaseBuilding::SelectActor_Implementation(const bool Select)
{
	SelectedIndicator->SetHiddenInGame(!Select);  // Show or hide selection indicator
}

void ATKBaseBuilding::SetFaction_Implementation(int32 NewFaction)
{
	FactionID = NewFaction;
}

int32 ATKBaseBuilding::GetFaction_Implementation()
{
	return FactionID;
}

