// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TopDownHUD.generated.h"

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

	TArray<AActor*> SelectedActors; // Currently selected actors

	void SelectActorInRect();

protected:
	virtual void DrawHUD() override;

public:
	//// --- Formation Settings ---
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Formation")
	//float UnitSpacing = 200.f;  // 每个单位的间距

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Formation")
	//bool bUseCircularFormation = false; // 是否启用圆形阵型

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Formation")
	//float CircularFormationRadius = 300.f; // 圆形阵型半径基数

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Formation")
	//bool bCenterFormationOnClick = true; // 是否以鼠标点击点为阵型中心


	void ShowSelectionRect(const FVector2D& Start, const FVector2D& Size);
	void HideSelectionRect();

	TArray<AActor*> GetSelectedActors();
};
