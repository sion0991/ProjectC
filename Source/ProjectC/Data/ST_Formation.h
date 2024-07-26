// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ST_Formation.generated.h"

USTRUCT(BlueprintType)
struct PROJECTC_API FST_Formation : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	FST_Formation() {}
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Character;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Position;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Formation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Group;
};
