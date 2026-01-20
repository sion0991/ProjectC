// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/RPGCharacter.h"
#include "RPGVilligeCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTC_API ARPGVilligeCharacter : public ARPGCharacter
{
	GENERATED_BODY()
private:
	virtual void InitializeAttributes() override;
public:
	virtual void HungryChanged(const FOnAttributeChangeData& Data);
	virtual void FatigueChanged(const FOnAttributeChangeData& Data);
	virtual void EnergyChanged(const FOnAttributeChangeData& Data);
};
