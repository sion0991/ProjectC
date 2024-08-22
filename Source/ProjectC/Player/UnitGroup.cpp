// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitGroup.h"
#include "Character/RPGCharacter.h"
#include "GameFramework/Controller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

UUnitGroup::UUnitGroup()
	: bTickable(true), bTickableWhenPaused(false)
{
	TroopWidth = 2000.f;
	IsTroopSet = false;
	GroupTransform = FTransform::Identity;
	Interval = 0;
	StartX = 0;
}

void UUnitGroup::Tick(float DeltaTime)
{
	/*if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("World delta for current frame equals %f"), GetWorld()->TimeSeconds));*/

	//SetRotate
	//GroupTransform.SetRotation();
}

bool UUnitGroup::IsTickable() const
{
	return bTickable;
}

bool UUnitGroup::IsTickableInEditor() const
{
	return bTickable;
}

bool UUnitGroup::IsTickableWhenPaused() const
{
	return bTickableWhenPaused;
}

TStatId UUnitGroup::GetStatId() const
{
	return TStatId();
}

UWorld* UUnitGroup::GetWorld() const
{
	return GetOuter()->GetWorld();
}

void UUnitGroup::LocationSetting()
{
	int NumOfTroop = Troops.Num();
	if (NumOfTroop < 2)
	{
		PosXs.AddUnique(0);
		if (!IsTroopSet)
		{
			Troops[0]->SetActorTransform(GroupTransform);
		}
	}
	else
	{
		Interval = TroopWidth / (NumOfTroop-1);
		StartX = -TroopWidth / 2.f;
		for (int i = 0; i < NumOfTroop; i++)
		{
			float PosX = StartX + i * Interval;
			PosXs.AddUnique(PosX);

			if (!IsTroopSet)
			{
				FTransform NewT = GroupTransform + FTransform(FVector(0.f, PosX, 0.f) * GroupTransform.GetRotation().GetRightVector());
				Troops[i]->SetActorTransform(NewT);
			}
				
		}
	}
}

void UUnitGroup::AddTroop(ARPGCharacter* Troop)
{
	Troops.Add(Troop);
}

void UUnitGroup::CalculationDir(FVector Target)
{
	FVector Dir = (Target - GroupTransform.GetLocation()).GetSafeNormal();
	Dir.Z = 0;
	//GroupTransform.SetRotation(FRotator(0, FMath::RadiansToDegrees(Dir), 0).Quaternion());
	GroupTransform.SetRotation(UKismetMathLibrary::MakeRotFromX(Dir).Quaternion());
	GroupTransform.SetLocation(Target);
}

//FVector UUnitGroup::CalculateTroopLocation(int index)
//{
//	return GroupTransform.GetRotation().GetNormalized() * FVector(0, PosXs[index],0);
//}

FVector UUnitGroup::CalculateTroopLocation(int index, int Formation)
{
	FVector Offset = Formations[Formation];
	if (Formation == 2)
	{
		Offset.Y *= index % 2 == 1 ? -1 : 1;
		Offset *= FMath::CeilToInt(index / 2.f) * Interval;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("%f"), FMath::CeilToDouble(index / 2.f)));
		return GroupTransform.GetRotation().GetNormalized() * Offset;
	}
	return GroupTransform.GetRotation().GetNormalized() * Offset * PosXs[index];
}

void UUnitGroup::SelectGroop()
{
	for (ARPGCharacter* Troop : Troops)
	{
		Troop->IsSelect(true);
	}
}

//void UUnitGroup::GroupMove(FVector Location)
//{
//	CalculationDir(Location);
//
//	for (int i = 0; i < Troops.Num(); i++)
//	{
//		FVector NewLocation = Location + CalculateTroopLocation(i);
//		Troops[i]->GetController()->FindComponentByClass<UBlackboardComponent>()->SetValueAsVector(FName(TEXT("TargetLocation")), NewLocation);
//		Troops[i]->SetTroopLocation(NewLocation);
//	}
//}

void UUnitGroup::GroupMove(FVector Location, int Formation)
{
	CalculationDir(Location);
	for (int i = 0; i < Troops.Num(); i++)
	{
		FVector NewLocation = Location + CalculateTroopLocation(i, Formation);
		GetBlackboardAsTroop(Troops[i])->SetValueAsVector(FName(TEXT("TargetLocation")), NewLocation);
		Troops[i]->SetTroopLocation(NewLocation);
	}
}

void UUnitGroup::SetEnemy(ARPGCharacter* _Enemy)
{
	Enemy = _Enemy;
	for (ARPGCharacter* Troop : Troops)
	{
		Troop->SetEnemy(_Enemy);
	}
}

UBlackboardComponent* UUnitGroup::GetBlackboardAsTroop(ARPGCharacter* Target)
{
	return Target->GetController()->FindComponentByClass<UBlackboardComponent>();
}

//UBlackboardComponent* UUnitGroup::GetBlackboard(ARPGCharacter* Target)
//{
//	//UBlackboardComponent* Blackboard = Target->GetController()->FindComponentByClass<UBlackboardComponent>();
//	
//	return Cast<AAIController>(Target->GetController())->GetBlackboardComponent();
//}
