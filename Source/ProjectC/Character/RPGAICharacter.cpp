// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RPGAICharacter.h"

void ARPGAICharacter::SetTroopLocation(FVector _TroopLocation, bool _HasFormation)
{
	TroopLocation = _TroopLocation;
	HasFormation = true;
}