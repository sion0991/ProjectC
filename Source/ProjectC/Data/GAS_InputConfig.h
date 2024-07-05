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
	//������ �±׿� ���õ� ù ��° �Է� �۾��� ��ȯ
	const UInputAction* FindNativeInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = true) const;
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = true) const;

	//�����ڰ� ����ϴ� �Է� �۾� ���. �Է� �۾��� ���� �÷��� �±׿� ���εǸ� �������� ���ε��ؾ���.

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputActions"))
	TArray<FTagInputAction> NativeInputActions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputActions"))
	TArray<FTagInputAction> AbilityInputActions;
};
