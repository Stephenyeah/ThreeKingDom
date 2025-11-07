// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TopDownHUD.generated.h"


class ATKBasePawn;
/**
 * 
 */
UCLASS()
class TOPDOWN_UTILITIES_API ATopDownHUD : public AHUD
{
	GENERATED_BODY()
	

private:
	// --- Selection Rectangle ---
	bool bDrawSelectionRect = false; // Is true when we need to draw the selection rectangle
	bool bSelectActors = false;
	FVector2D SelectionRectStart;
	FVector2D SelectionRectSize;
	FLinearColor SelectionRectColor = FLinearColor(1.f,0.f,0.f, .2f);

	TArray<ATKBasePawn*> SelectedActors; // Currently selected actors

	void SelectActorInRect();

protected:
	virtual void DrawHUD() override;

public:

	void ShowSelectionRect(const FVector2D& Start, const FVector2D& Size);
	void HideSelectionRect();

	TArray<ATKBasePawn*> GetSelectedActors();
};
