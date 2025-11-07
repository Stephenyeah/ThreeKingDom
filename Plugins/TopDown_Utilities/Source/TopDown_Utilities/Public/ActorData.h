// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonENUMS.h"
#include "AttributeSet.h"
#include "ActorData.generated.h"

/**
 *
 */

USTRUCT(BlueprintType)
struct FActorData : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
    EActorType ActorType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
    FString DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
    TSoftObjectPtr<UTexture2D> Texture;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
    TSoftObjectPtr<UMaterialInterface> IconMaterial;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
    int32 BaseHealth;

    FActorData() : ActorType(EActorType::Spearmen), DisplayName(TEXT("")), Texture(nullptr), BaseHealth(100) {}

    FActorData(EActorType Type, FString Name, UTexture2D* Tex, int32 Default)
        : ActorType(Type), DisplayName(Name), Texture(Tex), BaseHealth(Default) {
    }
};

USTRUCT(BlueprintType)
struct FActorBuildCost : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
    EActorType ActorType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
    TMap<FGameplayAttribute, int32> BuildCost;
};
