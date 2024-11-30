// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/RPGCharacter.h"
#include "RPGAICharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTC_API ARPGAICharacter : public ARPGCharacter
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack, meta = (AllowPrivateAccess = "true"))
	float MoveRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack, meta = (AllowPrivateAccess = "true"))
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Troop, meta = (AllowPrivateAccess = "true"))
	FVector TroopLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Troop, meta = (AllowPrivateAccess = "true"))
	bool HasFormation;
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Troop")
	void IsSelect(bool IsSelected);

	void SetTroopLocation(FVector _TroopLocation, bool _HasFormation);

	UFUNCTION(BlueprintImplementableEvent, Category = "Troop")
	void SetEnemy(AActor* Enemy);
};
