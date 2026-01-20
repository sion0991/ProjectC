// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "Data/GAS_InputConfig.h"
#include "GameplayTagContainer.h"
#include "RPGEnhancedInputComponent.generated.h"

/**
 *
 */
UCLASS()
class PROJECTC_API URPGEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserClass, typename FuncType>
	void BindActionByTag(const UGAS_InputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func)
	{
		check(InputConfig);

		if (const UInputAction* IA = InputConfig->FindAbilityInputActionForTag(InputTag))
			BindAction(IA, TriggerEvent, Object, Func);
	}

	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
	void BindAbilityActions(const UGAS_InputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, TArray<uint32>& BindHandles)
	{
		check(InputConfig);
		UE_LOG(LogTemp, Warning, TEXT("bind"));
		for (const FTagInputAction& Action : InputConfig->AbilityInputActions)
		{
			if (Action.InputAction && Action.InputTag.IsValid())
			{
				UE_LOG(LogTemp, Warning, TEXT("%s bind"), *Action.InputTag.GetTagName().ToString());
				if (PressedFunc)
					BindHandles.Add(BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, PressedFunc, Action.InputTag).GetHandle());

				if (ReleasedFunc)
					BindHandles.Add(BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag).GetHandle());
			}
		}
	}
};

//template<class UserClass, typename FuncType>
//void URPGEnhancedInputComponent::BindActionByTag(const UGAS_InputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func)
//{
//	check(InputConfig);
//
//	if (const UInputAction* IA = InputConfig->FindInputActionForTag(InputTag))
//		BindAction(IA, TriggerEvent, Object, Func);
//}