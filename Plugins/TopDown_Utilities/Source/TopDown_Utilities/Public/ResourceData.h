// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonENUMS.h"
#include "ResourceData.generated.h"
/**
 * 
 */

USTRUCT(BlueprintType)
struct FResourceData : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
    EResourceTypes ResourceType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
    FString DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
    UTexture2D* Texture;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
    int32 DefaultValue;

    FResourceData() : ResourceType(EResourceTypes::Wood), DisplayName(TEXT("")), Texture(nullptr), DefaultValue(0) {}

    FResourceData(EResourceTypes Type, FString Name, UTexture2D* Tex, int32 Default)
        : ResourceType(Type), DisplayName(Name), Texture(Tex), DefaultValue(Default) {
    }

};