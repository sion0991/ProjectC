// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGPlayerState.h"
#include "AbilitySystem/RPGAbilitySystemComponent.h"
#include "AbilitySystem/RPGAttributeSet.h"

ARPGPlayerState::ARPGPlayerState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//NetUpdateFrequency = 100.f;
}

APlayerController* ARPGPlayerState::GetRPGPlayerController() const
{
	return Cast<APlayerController>(GetOwningController());
}

//UAbilitySystemComponent* ARPGPlayerState::GetAbilitySystemComponent() const
//{
//	return AbilitySystemComponent;
//}
