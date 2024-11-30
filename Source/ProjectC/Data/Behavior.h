// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EBehavior : uint8
{
	Idle	UMETA(DisplayName = "Idle"),
	Wander	UMETA(DisplayName = "Wandering"),
	Train	UMETA(DisplayName = "Training"),
	Rest	UMETA(DisplayName = "Rest"),
	Sleep	UMETA(DisplayName = "Sleep"),
	Eat		UMETA(DisplayName = "Eat"),
	Research	UMETA(DisplayName = "Research"),
	Craft	UMETA(DisplayName = "Craft"),
	Fight	UMETA(DisplayName = "Fight"),
	Dead	UMETA(DisplayName = "Dead")
};
