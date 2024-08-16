// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DataTableManager.generated.h"

class UDataTable;

UCLASS()
class PROJECTC_API UDataTableManager : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "Save"))
	static bool SaveArrayText(FString SaveDir, FString FileName, TArray<FString> SaveText, bool AllowOverWriting);
	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "Save"))
	static bool SaveDataTableToCSV(FString SaveDir, FString FileName, UDataTable* DataTable, bool AllowOverWriting);
	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "Load"))
	static void LoadCSVToDataTable(FString LoadDir, FString FileName, UDataTable* DataTable);
	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "Row"))
	static void AddFormationRow(FName RowName, FST_Formation Row, UDataTable* DataTable);
	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "Row"))
	static void ResetDataTable(UDataTable* DataTable);
	/*UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "Row"))
	static void GetAllRowAtDataTable(UDataTable* DataTable, TArray<struct T>& Rows);*/
};
