// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RPGPlayerController.generated.h"

class UInventorySystemComponent;

UCLASS()
class PROJECTC_API ARPGPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	TWeakObjectPtr<UInventorySystemComponent> InventorySystemComponent;

	virtual void OnRep_PlayerState() override;

public:
	UInventorySystemComponent* GetInventorySystemComponent() const;
};
