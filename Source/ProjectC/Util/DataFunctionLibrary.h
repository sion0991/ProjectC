// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DataFunctionLibrary.generated.h"

class USG_PlayerData;
class UDataTable;

UCLASS()
class PROJECTC_API UDataFunctionLibrary : public UBlueprintFunctionLibrary
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

private:
	static void ItemUpdate(USG_PlayerData* Data, FString SlotName, int UserIndex);
public:
	static void LoadGame(FString SlotName, int UserIndex, USG_PlayerData*& Data);
	//static void SaveGame(APC_Player* Player, FString SlotName, int UserIndex);
	static USG_PlayerData* GetSaveData(bool& HasData, FString SlotName = "Data", int UserIndex = 0);
	static UDataTable* GetItemTable();
	template<typename Enumeration>
	FORCEINLINE static FName GetEnumDisplayNameToName(const Enumeration Enumer)
	{
		int32 ConvertEnum = static_cast<uint8>(Enumer);
		return FName(StaticEnum<Enumeration>()->GetDisplayNameTextByValue(ConvertEnum).ToString());
	}
	template <typename T>
	FORCEINLINE static void SetArrayElement(TArray<T>& item_array, int32 index, T item)
	{
		if (item_array.Num() - 1 < index)
			item_array.SetNum(index);

		item_array.Insert(item, index);
	}
};
