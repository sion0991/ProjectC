// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGPlayerController.h"
#include "RPGPlayerState.h"
#include "System/InventorySystemComponent.h"
void ARPGPlayerController::OnRep_PlayerState()
{
	ARPGPlayerState* PS = GetPlayerState<ARPGPlayerState>();
	if (PS)
	{
		InventorySystemComponent = Cast<UInventorySystemComponent>(PS->GetInventorySystemComponent());
		//LoadData();
	}
}

UInventorySystemComponent* ARPGPlayerController::GetInventorySystemComponent() const
{
	return InventorySystemComponent.Get();
}
