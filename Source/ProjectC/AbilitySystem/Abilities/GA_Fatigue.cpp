// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Fatigue.h"
#include "AbilitySystemComponent.h"

UGA_Fatigue::UGA_Fatigue()
{
	AbilityInputTag = FGameplayTag::RequestGameplayTag(TEXT("Ability.NoCost.RegenHP"));
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("Ability.NoCost.RegenHP")));
	ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.NoCost.RegenHP")));
}

void UGA_Fatigue::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (CommitAbility(Handle, ActorInfo, ActivationInfo))
	{

	}
	else
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	}
}

void UGA_Fatigue::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (IsEndAbilityValid(Handle, ActorInfo))
	{
		UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
		if (ASC)
		{
			if (EffectHandle.IsValid())
			{
				if (ASC->RemoveActiveGameplayEffect(EffectHandle))
				{
					EffectHandle.Invalidate();
				}
			}
		}
		Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	}
}
