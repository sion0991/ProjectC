// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "GAS_InputConfig.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct FTagInputAction
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	const UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "InputTag")
	FGameplayTag InputTag;
};
/**
 * 
 */
UCLASS()
class PROJECTC_API UGAS_InputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	//지정된 태그와 관련된 첫 번째 입력 작업을 반환
	const UInputAction* FindNativeInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = true) const;
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = true) const;

	//소유자가 사용하는 입력 작업 목록. 입력 작업은 게임 플레이 태그에 매핑되며 수동으로 바인딩해야함.

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputActions"))
	TArray<FTagInputAction> NativeInputActions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputActions"))
	TArray<FTagInputAction> AbilityInputActions;
};
