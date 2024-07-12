// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
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
class PROJECTC_API ARPGCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GAS, meta = (AllowPrivateAccess = "true"))
	URPGAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GAS, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<URPGGameplayAbility>> Abilities;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GAS, meta = (AllowPrivateAccess = "true"))
	URPGAttributeSet* AttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GAS, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<class UGameplayEffect>> DefaultEffects;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parts, meta = (AllowPrivateAccess = "true"))
	UGAS_InputConfig* InputConfig;
public:
	// Sets default values for this character's properties
	ARPGCharacter();

	
protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	void InputAbilitySystemInputTagPressed(FGameplayTag InputTag);
	void InputAbilitySystemInputTagReleased(FGameplayTag InputTag);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

private:
	void InitializeAttributes();
	void GiveAbilities();

protected:
	virtual void HPChanged(const FOnAttributeChangeData& Data);
	UFUNCTION(BlueprintImplementableEvent, Category = Attribute)
	void Death();
	UFUNCTION(BlueprintCallable, Category = Attribute)
	void AttackToTarget(ARPGCharacter* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass);

};
