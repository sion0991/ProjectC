// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/RPGCharacter.h"
#include "RPGPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTC_API ARPGPlayerCharacter : public ARPGCharacter
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

public:
	ARPGPlayerCharacter();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void OnRep_PlayerState() override;

	void InputAbilitySystemInputTagPressed(FGameplayTag InputTag);
	void InputAbilitySystemInputTagReleased(FGameplayTag InputTag);
};
