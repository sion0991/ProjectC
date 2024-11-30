// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGVilligeCharacter.h"
#include "AbilitySystem/RPGAbilitySystemComponent.h"
#include "AbilitySystem/RPGAttributeSet.h"

void ARPGVilligeCharacter::InitializeAttributes()
{
	Super::InitializeAttributes();

	if (GetAbilitySystemComponent())
	{
		GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHungryAttribute()).AddUObject(this, &ARPGVilligeCharacter::HungryChanged);
		GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetFatigueAttribute()).AddUObject(this, &ARPGVilligeCharacter::FatigueChanged);
		GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetEnergyAttribute()).AddUObject(this, &ARPGVilligeCharacter::EnergyChanged);
	}
}

void ARPGVilligeCharacter::HungryChanged(const FOnAttributeChangeData& Data)
{

}

void ARPGVilligeCharacter::FatigueChanged(const FOnAttributeChangeData& Data)
{
}

void ARPGVilligeCharacter::EnergyChanged(const FOnAttributeChangeData& Data)
{
}
