// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/Behavior.h"

#include "AC_Behavior.generated.h"

struct FOnAttributeChangeData;

//UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
UCLASS(BlueprintType, Blueprintable)
class PROJECTC_API UAC_Behavior : public UActorComponent
{
	GENERATED_BODY()

private:
	TQueue<EBehavior> BehaviorPriorities;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status, meta = (AllowPrivateAccess = "true"))
	float HungryToAct;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status, meta = (AllowPrivateAccess = "true"))
	float EnergyToAct;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status, meta = (AllowPrivateAccess = "true"))
	float FatigueToAct;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status, meta = (AllowPrivateAccess = "true"))
	bool ActHungry;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status, meta = (AllowPrivateAccess = "true"))
	bool ActFatigue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status, meta = (AllowPrivateAccess = "true"))
	bool ActEnergy;

	class ARPGCharacter* OwningPlayer;
	class UBlackboardComponent* BlackboardComponent;
public:	
	// Sets default values for this component's properties
	UAC_Behavior();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void HungryChanged(const FOnAttributeChangeData& Data);
	virtual void FatigueChanged(const FOnAttributeChangeData& Data);
	virtual void EnergyChanged(const FOnAttributeChangeData& Data);

	UFUNCTION(BlueprintImplementableEvent, Category = Attribute)
	void Hungry();
	UFUNCTION(BlueprintImplementableEvent, Category = Attribute)
	void Fatigue();
	UFUNCTION(BlueprintImplementableEvent, Category = Attribute)
	void Energy();
	UFUNCTION(BlueprintPure, Category= Behavior)
	bool IsDoingBehavior(EBehavior behavior);
	UFUNCTION(BlueprintCallable, Category = Behavior)
	void ChangeBehavior();
	UFUNCTION(BlueprintCallable, Category = Behavior)
	void AddBehavior(EBehavior behavior);
	UFUNCTION(BlueprintCallable, Category = Behavior)
	void AddChangeBehavior(EBehavior behavior);
	UFUNCTION(BlueprintCallable, Category = Behavior)
	void UseBehavior();

	UFUNCTION(BlueprintPure, Category = Behavior)
	EBehavior GetCurrentBehavior();
	void SetCurrentBehavior(EBehavior behavior);

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void SetBlackBoard(class UBlackboardComponent* blackboard);
};
