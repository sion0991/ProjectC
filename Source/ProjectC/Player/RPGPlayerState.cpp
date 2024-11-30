// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGPlayerState.h"
#include "System/InventorySystemComponent.h"
#include "AbilitySystem/RPGAbilitySystemComponent.h"
#include "AbilitySystem/RPGAttributeSet.h"
#include "Net/UnrealNetwork.h"


ARPGPlayerState::ARPGPlayerState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	InventorySystemComponent = CreateDefaultSubobject<UInventorySystemComponent>(TEXT("InventorySystemComponent"));
	InventorySystemComponent->SetIsReplicated(true);


	NetUpdateFrequency = 100.f;

}

APlayerController* ARPGPlayerState::GetRPGPlayerController() const
{
	return Cast<APlayerController>(GetOwningController());
}

UInventorySystemComponent* ARPGPlayerState::GetInventorySystemComponent() const
{
	return InventorySystemComponent;
}

void ARPGPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARPGPlayerState, Inventory);
}

FInventory* ARPGPlayerState::GetInventory()
{
	return &Inventory;
}

//UAbilitySystemComponent* ARPGPlayerState::GetAbilitySystemComponent() const
//{
//	return AbilitySystemComponent;
//}
