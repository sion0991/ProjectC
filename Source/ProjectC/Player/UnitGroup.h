// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Tickable.h"
#include "UnitGroup.generated.h"

class UBlackboardComponent;
class ARPGAICharacter;
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
    void LocationSetting(bool isTroopSet);
    UFUNCTION(BlueprintCallable, Category = "Group")
    void AddTroop(ARPGAICharacter* Troop);
    UFUNCTION(BlueprintCallable, Category = "Group")
    void CalculationDir(FVector Target);
    /*UFUNCTION(BlueprintCallable, Category = "Group")
    FVector CalculateTroopLocation(int index);*/
    UFUNCTION(BlueprintCallable, Category = "Group")
    FVector CalculateTroopLocation(int index, int Formation =0);
    UFUNCTION(BlueprintCallable, Category = "Group")
    void SelectGroop(bool IsSelect);
    /*UFUNCTION(BlueprintCallable, Category= "Group")
    void GroupMove(FVector Location);*/
    UFUNCTION(BlueprintCallable, Category = "Group")
    void GroupMove(FVector Location,int Formation =0);

    UFUNCTION(BlueprintCallable, Category = "Group")
    void SetEnemy(ARPGCharacter* _Enemy);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Troop")
    int TroopWidth;
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tick")
    bool bTickable;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tick")
    bool bTickableWhenPaused;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Troop")
    TArray<ARPGAICharacter*> Troops;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Troop")
    FTransform GroupTransform;
private:
    UBlackboardComponent* GetBlackboardAsTroop(ARPGAICharacter* Target);
    float Interval;
    float StartX;
    TArray<float> PosXs;
    TArray<FVector> Formations =
    {
        FVector(0.f,1.f,0.f),
        FVector(1.f,0.f,0.f),
        FVector(-1.f,1.f,0.f)
    };
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy", meta = (AllowPrivateAccess = "true"))
    ARPGCharacter* Enemy;

};
