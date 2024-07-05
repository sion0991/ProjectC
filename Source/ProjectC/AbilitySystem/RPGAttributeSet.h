// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "RPGAttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class PROJECTC_API URPGAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, Category = "HP", ReplicatedUsing = OnRep_HP)
	FGameplayAttributeData HP;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, HP)

	// MaxHP is its own attribute since GameplayEffects may modify it
	UPROPERTY(BlueprintReadOnly, Category = "HP", ReplicatedUsing = OnRep_MaxHP)
	FGameplayAttributeData MaxHP;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, MaxHP)

	// HP regen rate will passively increase HP every second
	UPROPERTY(BlueprintReadOnly, Category = "HP", ReplicatedUsing = OnRep_HPRegenRate)
	FGameplayAttributeData HPRegenRate;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, HPRegenRate)

	// Current MP, used to execute special abilities. Capped by MaxMP.
	UPROPERTY(BlueprintReadOnly, Category = "MP", ReplicatedUsing = OnRep_MP)
	FGameplayAttributeData MP;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, MP)

	// MaxMP is its own attribute since GameplayEffects may modify it
	UPROPERTY(BlueprintReadOnly, Category = "MP", ReplicatedUsing = OnRep_MaxMP)
	FGameplayAttributeData MaxMP;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, MaxMP)

	// MP regen rate will passively increase MP every second
	UPROPERTY(BlueprintReadOnly, Category = "MP", ReplicatedUsing = OnRep_MPRegenRate)
	FGameplayAttributeData MPRegenRate;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, MPRegenRate)

public:
	URPGAttributeSet();

	void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	//virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
protected:
	UFUNCTION()
	virtual void OnRep_HP(const FGameplayAttributeData& OldHP);

	UFUNCTION()
	virtual void OnRep_MaxHP(const FGameplayAttributeData& OldMaxHP);

	UFUNCTION()
	virtual void OnRep_HPRegenRate(const FGameplayAttributeData& OldHPRegenRate);

	UFUNCTION()
	virtual void OnRep_MP(const FGameplayAttributeData& OldMP);

	UFUNCTION()
	virtual void OnRep_MaxMP(const FGameplayAttributeData& OldMaxMP);

	UFUNCTION()
	virtual void OnRep_MPRegenRate(const FGameplayAttributeData& OldMPRegenRate);
};
