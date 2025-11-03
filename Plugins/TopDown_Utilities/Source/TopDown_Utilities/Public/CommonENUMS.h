

#pragma once

UENUM(BlueprintType)
enum class EResourceTypes : uint8
{
	Wood UMETA(DisplayName = "Wood"),
	Food UMETA(DisplayName = "Food"),
	Gold UMETA(DisplayName = "Gold"),
	Stone UMETA(DisplayName = "Stone"),
	Population UMETA(DisplayName = "Population")
	
};


UENUM(BlueprintType)
enum class EPawnType : uint8
{
	Cavalry UMETA(DisplayName = "Cavalry"),
	Spearmen UMETA(DisplayName = "Spearmen"),
	Infantry UMETA(DisplayName = "Infantry"),
	Archers UMETA(DisplayName = "Archers"),

};
