// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ST_StatusBase.generated.h"

USTRUCT(BlueprintType)
struct PROJECTC_API FST_StatusBase : public FTableRowBase
{
	GENERATED_BODY()

public:

	FST_StatusBase() {}
};
