// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CalculateLibrary.generated.h"

class AActor;

UCLASS()
class PROJECTC_API UCalculateLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/*UFUNCTION(BlueprintCallable, Category = "Calculate", meta = (Keywords = "Calculate"))
	void GetDistanceXYofActors(AActor* From, AActor* To);*/
};
