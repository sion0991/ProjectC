// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_Behavior.h"
#include "../RPGCharacter.h"
#include "AbilitySystem/RPGAbilitySystemComponent.h"
#include "AbilitySystem/RPGAttributeSet.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Misc/OutputDeviceNull.h"

UAC_Behavior::UAC_Behavior()
{
	PrimaryComponentTick.bCanEverTick = true;
	ActHungry = false;
	ActFatigue = false;
	ActEnergy = false;
	OwningPlayer = Cast<ARPGCharacter>(GetOwner());
}


// Called when the game starts
void UAC_Behavior::BeginPlay()
{
	Super::BeginPlay();
	
	OwningPlayer->GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(OwningPlayer->GetAttribute()->GetEnergyAttribute()).AddUObject(this, &UAC_Behavior::EnergyChanged);
	OwningPlayer->GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(OwningPlayer->GetAttribute()->GetHungryAttribute()).AddUObject(this, &UAC_Behavior::HungryChanged);
	OwningPlayer->GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(OwningPlayer->GetAttribute()->GetFatigueAttribute()).AddUObject(this, &UAC_Behavior::FatigueChanged);
}


// Called every frame
void UAC_Behavior::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAC_Behavior::HungryChanged(const FOnAttributeChangeData& Data)
{
	if (HungryToAct >= Data.NewValue && !ActHungry)
	{
		ActHungry = true;
		Hungry();
	}
	else if(HungryToAct < Data.NewValue)
	{
		ActHungry = false;
	}
}

void UAC_Behavior::FatigueChanged(const FOnAttributeChangeData& Data)
{
	if (FatigueToAct >= Data.NewValue && !ActFatigue)
	{
		ActFatigue = true;
		Fatigue();
	}
	else if (FatigueToAct < Data.NewValue)
	{
		ActFatigue = false;
	}
}

void UAC_Behavior::EnergyChanged(const FOnAttributeChangeData& Data)
{
	if (EnergyToAct >= Data.NewValue && !ActEnergy)
	{
		ActEnergy = true;
		Energy();
	}
	else if (EnergyToAct < Data.NewValue)
	{
		ActEnergy = false;
	}
}

bool UAC_Behavior::IsDoingBehavior(EBehavior behavior)
{
	return GetCurrentBehavior() == behavior;
}

void UAC_Behavior::ChangeBehavior()
{
	OwningPlayer->StopAnimMontage(OwningPlayer->GetCurrentMontage());
	if(!BehaviorPriorities.IsEmpty())
		BehaviorPriorities.Pop();
	FOutputDeviceNull Ar;
	UObject* UseObject = BlackboardComponent->GetValueAsObject("TargetPlace");
	if(UseObject)CallFunctionByNameWithArguments(TEXT("EndUse"), Ar, nullptr, true);
	UseBehavior();

}

void UAC_Behavior::AddBehavior(EBehavior behavior)
{
	BehaviorPriorities.Enqueue(behavior);
}

void UAC_Behavior::AddChangeBehavior(EBehavior behavior)
{
	OwningPlayer->StopAnimMontage(OwningPlayer->GetCurrentMontage());
	if (!BehaviorPriorities.IsEmpty())
		BehaviorPriorities.Pop();
	BehaviorPriorities.Enqueue(behavior);
	UseBehavior();
}

void UAC_Behavior::UseBehavior()
{
	EBehavior Temp;
	bool NotEmpty;
	NotEmpty = BehaviorPriorities.Peek(Temp);
	if (!NotEmpty)
		SetCurrentBehavior(EBehavior::Idle);
	else
		SetCurrentBehavior(Temp);
}

EBehavior UAC_Behavior::GetCurrentBehavior()
{
	return (EBehavior)BlackboardComponent->GetValueAsEnum("Behavior");
}

void UAC_Behavior::SetCurrentBehavior(EBehavior behavior)
{
	BlackboardComponent->SetValueAsEnum(FName("Behavior"), (uint8)behavior);
}

void UAC_Behavior::SetBlackBoard(UBlackboardComponent* blackboard)
{
	BlackboardComponent = blackboard;
}
