// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventorySystemComponent.generated.h"

struct FST_Item;
class ARPGPlayerState;

UCLASS(Blueprintable)
class PROJECTC_API UInventorySystemComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	ARPGPlayerState* GetPlayerState();
public:	
	void AddItem(const FST_Item& Item);
	void AddItemInBattle(const FST_Item& Item);
	void SubItem(const int Itemindex);
	void SubItemInBattle(const int Itemindex);
	void Load(const FString SlotName);
};
