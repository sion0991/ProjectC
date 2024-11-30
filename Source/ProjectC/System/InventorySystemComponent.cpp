#include "InventorySystemComponent.h"
//#include "Data/ST_Item.h"
#include "Player/RPGPlayerState.h"

#define InventoryItem GetPlayerState()->GetInventory()

ARPGPlayerState* UInventorySystemComponent::GetPlayerState()
{
	return Cast<ARPGPlayerState>(GetOwner());
}

void UInventorySystemComponent::AddItem(const FST_Item& Item)
{
	InventoryItem->InventoryItems.Add(Item);
}

void UInventorySystemComponent::AddItemInBattle(const FST_Item& Item)
{
	if (InventoryItem->MaxAcquisitionWeight >= InventoryItem->CurrentAcquisitionWeight + Item.Weight)
		InventoryItem->InventoryItems.Add(Item);
	else
		UE_LOG(LogTemp, Warning, TEXT("Too Much Weight "));
}

void UInventorySystemComponent::SubItem(const int Itemindex)
{
	InventoryItem->InventoryItems.RemoveAt(Itemindex);
}

void UInventorySystemComponent::SubItemInBattle(const int Itemindex)
{
	InventoryItem->CurrentAcquisitionWeight -= InventoryItem->InventoryItems[Itemindex].Weight;
	InventoryItem->InventoryItems.RemoveAt(Itemindex);
}

void UInventorySystemComponent::Load(const FString SlotName)
{
	//InventoryItem->EquipItems = 
}

