// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGAbilitySystemComponent.h"

void URPGAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& InputTag)
{
	UE_LOG(LogTemp, Warning, TEXT("Tag = %s"), *InputTag.GetTagName().ToString());
	if (InputTag.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Tag is Valid"));
		for (FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items)
		{
			TArray<FGameplayTag> AbilityTags;
			AbilitySpec.DynamicAbilityTags.GetGameplayTagArray(AbilityTags);
			for (auto AbilityTag : AbilityTags)
			{
				UE_LOG(LogTemp, Warning, TEXT("Ability Spec : %s"), *AbilityTag.GetTagName().ToString());
			}
			if (AbilitySpec.Ability && (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag)))
			{
				UE_LOG(LogTemp, Warning, TEXT("Has Tag And Ability"));
				if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
				{
					UE_LOG(LogTemp, Warning, TEXT("Has DynamicTag"));
					/*InputPressedSpecHandles.AddUnique(AbilitySpec.Handle);
					InputHeldSpecHandles.AddUnique(AbilitySpec.Handle);*/
					TryActivateAbilitiesByTag(FGameplayTagContainer(InputTag));
				}
			}

		}
	}
}

void URPGAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (InputTag.IsValid())
	{
		for (FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items)
		{
			if (AbilitySpec.Ability && (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag)))
			{
				/*InputReleasedSpecHandles.AddUnique(AbilitySpec.Handle);
				InputHeldSpecHandles.Remove(AbilitySpec.Handle);*/
				AbilitySpecInputReleased(AbilitySpec);
			}
		}
	}
}
