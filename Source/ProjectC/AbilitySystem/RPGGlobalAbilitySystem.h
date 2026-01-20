// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class ERPGAbilityInputID : uint8
{
	IA_None			UMETA(DisplayName = "IA_None"),
	IA_Ability1		UMETA(DisplayName = "IA_Ability1"),
	IA_Ability2		UMETA(DisplayName = "IA_Ability2"),
	IA_Ability3		UMETA(DisplayName = "IA_Ability3"),
	IA_Ability4		UMETA(DisplayName = "IA_Ability4"),
	IA_Sprint			UMETA(DisplayName = "IA_Sprint"),
	IA_Jump			UMETA(DisplayName = "IA_Jump")
};
/**
 * 
 */
class PROJECTC_API RPGGlobalAbilitySystem
{
public:
	RPGGlobalAbilitySystem();
	~RPGGlobalAbilitySystem();
};
