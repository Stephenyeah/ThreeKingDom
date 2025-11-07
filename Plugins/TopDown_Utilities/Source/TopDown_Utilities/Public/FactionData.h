// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FactionData.generated.h"

/**
 *
 */

USTRUCT()
struct FFactionData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Faction")
	FString FactionName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Faction")
	FLinearColor FactionColor;

	FFactionData() : FactionName(TEXT("Rebels")), FactionColor(FLinearColor::Blue) {}

};
