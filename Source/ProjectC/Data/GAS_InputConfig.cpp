// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS_InputConfig.h"

const UInputAction* UGAS_InputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const FTagInputAction& Action : AbilityInputActions)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, TEXT("InputConfig.h FindInputAction"));
		if (Action.InputAction && Action.InputTag.MatchesTagExact(InputTag))
			return Action.InputAction;
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for InputTag [%s] on InputConfig [%s]."), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}
