// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "RPGPlayerState.generated.h"

class UAbilitySystemComponent;
class URPGAbilitySystemComponent;
class URPGAttributeSet;
/**
 * 
 */
UCLASS()
class PROJECTC_API ARPGPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
private:
	// The ability system component sub-object used by player characters.
	UPROPERTY(VisibleAnywhere, Category = "RPG|PlayerState")
	TObjectPtr<URPGAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, Category = "RPG|PlayerState")
	URPGAttributeSet* AttributeSet;
public:
	ARPGPlayerState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category ="RPG|PlayerState")
	APlayerController* GetRPGPlayerController() const;

	UFUNCTION(BlueprintCallable, Category ="RPG|PlayerState")
	URPGAbilitySystemComponent* GetRPGAbilitySystemComponent() const { return AbilitySystemComponent; }
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	URPGAttributeSet* GetAttributeSet() const { return AttributeSet; }

};
