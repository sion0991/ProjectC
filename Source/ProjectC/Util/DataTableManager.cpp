// Fill out your copyright notice in the Description page of Project Settings.


#include "DataTableManager.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFileManager.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Engine/DataTable.h"
#include "Engine/UserDefinedStruct.h"
#include "../Data/ST_Formation.h"

bool UDataTableManager::SaveArrayText(FString SaveDir, FString FileName, TArray<FString> SaveText, bool AllowOverWriting)
{
	SaveDir += "\\";
	SaveDir += FileName;

	if (!AllowOverWriting)
	{
		if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*SaveDir))
		{
			return false;
		}
	}
	FString FinalString = "";
	for (FString& Each : SaveText)
	{
		FinalString += Each;
		FinalString += LINE_TERMINATOR;
	}

	return FFileHelper::SaveStringToFile(FinalString, *SaveDir);
}

bool UDataTableManager::SaveDataTableToCSV(FString SaveDir, FString FileName, UDataTable* DataTable, bool AllowOverWriting)
{
    if (!DataTable) 
    { 
        UE_LOG(LogTemp, Warning, TEXT("DataTable is null.")); 
        return false; 
    } 
    SaveDir += "\\";
    SaveDir += FileName;

    if (!AllowOverWriting)
    {
        if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*SaveDir))
        {
            return false;
        }
    }

    return FFileHelper::SaveStringToFile(DataTable->GetTableAsCSV(), *SaveDir);
}

void UDataTableManager::LoadCSVToDataTable(FString LoadDir, FString FileName, UDataTable* DataTable)
{
	LoadDir += "\\";
	LoadDir += FileName;
	if (FPaths::FileExists(LoadDir))
	{
		FString FileContent;
		// the csv file
		FFileHelper::LoadFileToString(FileContent, *LoadDir);
		TArray<FString> problems = DataTable->CreateTableFromCSVString(FileContent);

		if (problems.Num() > 0)
		{
			for (int32 ProbIdx = 0; ProbIdx < problems.Num(); ProbIdx++)
			{
				//Log the errors
				UE_LOG(LogTemp, Warning, TEXT("Not Loaded DataTable. %s"),&FileName);
			}
		}
		else
		{
			//Updated Successfully
			UE_LOG(LogTemp, Warning, TEXT("Success Load. %s"), &FileName);
		}
	}
}

void UDataTableManager::AddFormationRow(FName RowName, FST_Formation Row, UDataTable* DataTable)
{
	DataTable->AddRow(RowName, Row);
}