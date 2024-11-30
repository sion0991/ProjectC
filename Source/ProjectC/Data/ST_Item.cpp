// Fill out your copyright notice in the Description page of Project Settings.


#include "ST_Item.h"

FST_Item::FST_Item()
{
	ItemIndex = "";
	Category = EItemCategory::Cg_Equipment;
	ItemType = EItemType::Tp_RightWeapon;
	WeaponType = EWeaponType::Tp_Sword;
	EquipmentType = EEquipmentType::Tp_None;
	SkeletalMesh = NULL;
	Icon = NULL;
	PickUpText = FText();
	ActionText = FText();
	Stat.Reset();
	Duration = 0;
	BTransform = FTransform::Identity;
	ATransform = FTransform::Identity;
	BSocket = "";
	ASocket = "";
	Weight = 0;
}
