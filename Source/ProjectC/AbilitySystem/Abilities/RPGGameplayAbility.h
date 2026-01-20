// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystem/RPGGlobalAbilitySystem.h"
#include "RPGGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTC_API URPGGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = InputID)
	struct FGameplayTag AbilityInputTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Handles)
	mutable FActiveGameplayEffectHandle EffectHandle;
};
