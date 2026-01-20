// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GI_Game.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTC_API UGI_Game : public UGameInstance
{
	GENERATED_BODY()
public:
	UGI_Game();
	virtual void Init() override;
	virtual void Shutdown() override;
	virtual void StartGameInstance() override;
};
