// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GenericTeamAgentInterface.h"
#include "RPGCharacter.generated.h"

class URPGAbilitySystemComponent;
class UAbilitySystemComponent;
class URPGGameplayAbility;
class URPGAttributeSet;
class UInputMappingContext;
class UGAS_InputConfig;
struct FGameplayTag;
struct FOnAttributeChangeData;

UCLASS()
class PROJECTC_API ARPGCharacter : public ACharacter, public IAbilitySystemInterface, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = "true"))
	FGenericTeamId TeamId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State, meta = (AllowPrivateAccess = "true"))
	bool IsDeath;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GAS, meta = (AllowPrivateAccess = "true"))
	URPGAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GAS, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<URPGGameplayAbility>> Abilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GAS, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<class UGameplayEffect>> DefaultEffects;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GAS, meta = (AllowPrivateAccess = "true"))
	URPGAttributeSet* AttributeSet;
public:
	// Sets default values for this character's properties
	ARPGCharacter();

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interact)

protected:
	virtual void InitializeAttributes();
	
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

	virtual void HPChanged(const FOnAttributeChangeData& Data);
	UFUNCTION(BlueprintImplementableEvent, Category = Attribute)
	void Death();
	UFUNCTION(BlueprintCallable, Category = Attribute)
	void AttackToTarget(ARPGCharacter* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass);
	UFUNCTION(BlueprintCallable, Category = Attribute)
	void AttackToTargetAsCaller(ARPGCharacter* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass, FGameplayTag DataTag, float Value);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	URPGAttributeSet* GetAttribute();
private:
	void GiveAbilities();

	virtual FGenericTeamId GetGenericTeamId() const override { return TeamId; }
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GAS, meta = (AllowPrivateAccess = "true"))
	UGAS_InputConfig* InputConfig;

};
