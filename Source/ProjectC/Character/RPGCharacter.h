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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GAS, meta = (AllowPrivateAccess = "true"))
	UGAS_InputConfig* InputConfig;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack, meta = (AllowPrivateAccess = "true"))
	float MoveRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack, meta = (AllowPrivateAccess = "true"))
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Troop, meta = (AllowPrivateAccess = "true"))
	FVector TroopLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = "true"))
	FGenericTeamId TeamId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State, meta = (AllowPrivateAccess = "true"))
	bool IsDeath;
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

	UFUNCTION(BlueprintImplementableEvent, Category = "Troop")
	void IsSelect(bool IsSelected);

	void SetTroopLocation(FVector _TroopLocation);

	UFUNCTION(BlueprintImplementableEvent, Category = "Troop")
	void SetEnemy(AActor* Enemy);
private:
	void InitializeAttributes();
	void GiveAbilities();

	virtual FGenericTeamId GetGenericTeamId() const override { return TeamId; }
protected:
	virtual void HPChanged(const FOnAttributeChangeData& Data);
	UFUNCTION(BlueprintImplementableEvent, Category = Attribute)
	void Death();
	UFUNCTION(BlueprintCallable, Category = Attribute)
	void AttackToTarget(ARPGCharacter* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass);
};
