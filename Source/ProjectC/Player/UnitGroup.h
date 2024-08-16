// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Tickable.h"
#include "UnitGroup.generated.h"

class UBlackboardComponent;
class ARPGCharacter;

UCLASS(Blueprintable)
class PROJECTC_API UUnitGroup : public UObject, public FTickableGameObject
{
    GENERATED_BODY()

public:
    UUnitGroup();

    virtual void Tick(float DeltaTime) override;
    virtual bool IsTickable() const override;
    virtual bool IsTickableInEditor() const override;
    virtual bool IsTickableWhenPaused() const override;
    virtual TStatId GetStatId() const override;
    virtual UWorld* GetWorld() const override;

    UFUNCTION(BlueprintCallable, Category = "Group")
    void LocationSetting();
    UFUNCTION(BlueprintCallable, Category = "Group")
    void AddTroop(ARPGCharacter* Troop);
    UFUNCTION(BlueprintCallable, Category = "Group")
    void CalculationDir(FVector Target);
    UFUNCTION(BlueprintCallable, Category = "Group")
    FVector CalculateTroopLocation(int index);
    UFUNCTION(BlueprintCallable, Category = "Group")
    void SelectGroop();
    UFUNCTION(BlueprintCallable, Category= "Group")
    void GroupMove(FVector Location);

    UFUNCTION(BlueprintCallable, Category = "Group")
    void SetEnemy(ARPGCharacter* _Enemy);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Troop")
    int TroopWidth;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Troop")
    bool IsTroopSet;
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tick")
    bool bTickable;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tick")
    bool bTickableWhenPaused;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Troop")
    TArray<ARPGCharacter*> Troops;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Troop")
    FTransform GroupTransform;
private:
    //UBlackboardComponent* GetBlackboard(ARPGCharacter* Target);
    TArray<float> PosXs;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy", meta = (AllowPrivateAccess = "true"))
    ARPGCharacter* Enemy;

};
