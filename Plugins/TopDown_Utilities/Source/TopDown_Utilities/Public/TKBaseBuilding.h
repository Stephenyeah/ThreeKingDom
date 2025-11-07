// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SelectableInterface.h"
#include "GameFramework/Actor.h"
#include "FactionInterface.h"
#include "TKBaseBuilding.generated.h"

class UBoxComponent;

UCLASS()
class TOPDOWN_UTILITIES_API ATKBaseBuilding : public AActor, public ISelectableInterface, public IFactionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATKBaseBuilding();

private:
	//Box Collider
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> BoxComponent;

	//Mesh Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	//Selection Indicator
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> SelectedIndicator;


	// Faction ID
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	int32 FactionID = 1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Implement Selectable Interface
	void SelectActor_Implementation(const bool Select) override;

	void SetFaction_Implementation(int32 NewFaction) override;

	int32 GetFaction_Implementation() override;
};
