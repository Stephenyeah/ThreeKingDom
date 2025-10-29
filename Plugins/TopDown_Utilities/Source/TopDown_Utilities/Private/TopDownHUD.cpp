// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownHUD.h"


// Draw the HUD, including the selection rectangle if needed
void ATopDownHUD::DrawHUD()
{
	Super::DrawHUD();
	if (bDrawSelectionRect)
	{
		DrawRect(SelectionRectColor, SelectionRectStart.X, SelectionRectStart.Y, SelectionRectSize.X, SelectionRectSize.Y);
	}
	if(bSelectActors)
	{
		SelectActorInRect();
	}
}

// Show the selection rectangle
void ATopDownHUD::ShowSelectionRect(const FVector2D& InSelectionRectStart, const FVector2D& InSelectionRectSize)
{
	SelectionRectStart = InSelectionRectStart;
	SelectionRectSize = InSelectionRectSize;
	bDrawSelectionRect = true;

}

// Hide the selection rectangle
void ATopDownHUD::HideSelectionRect()
{
	bDrawSelectionRect = false;
	bSelectActors = true;

}

// Get the currently selected actors
TArray<AActor*> ATopDownHUD::GetSelectedActors()
{
	return  SelectedActors;

}

// Select actors within the selection rectangle
void ATopDownHUD::SelectActorInRect()
{
	SelectedActors.Empty();
	FVector2D FirstPoint = SelectionRectStart;
	FVector2D SecondPoint = SelectionRectStart + SelectionRectSize;
	GetActorsInSelectionRectangle<AActor>(FirstPoint, SecondPoint, SelectedActors, false);

	// Clear previous selection
	bSelectActors = false;

}