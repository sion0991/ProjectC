// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGPlayerCharacter.h"
#include "Player/RPGEnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/RPGAbilitySystemComponent.h"

ARPGPlayerCharacter::ARPGPlayerCharacter()
{
	OverrideInputComponentClass = URPGEnhancedInputComponent::StaticClass();
}

// Called to bind functionality to input
void ARPGPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Cast<APlayerController>(Controller)->GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	URPGEnhancedInputComponent* PEI = Cast<URPGEnhancedInputComponent>(PlayerInputComponent);
	if (PEI)
	{
		TArray<uint32> BindHandles;
		PEI->BindAbilityActions(InputConfig, this, &ARPGPlayerCharacter::InputAbilitySystemInputTagPressed, &ARPGPlayerCharacter::InputAbilitySystemInputTagReleased, BindHandles);
	}
}

void ARPGPlayerCharacter::OnRep_PlayerState()
{
	/*ARPGPlayerState* PS = GetPlayerState<ARPGPlayerState>();
	if (PS)
	{
		AbilitySystemComponent = Cast<URPGAbilitySystemComponent>(PS->GetAbilitySystemComponent());
		AbilitySystemComponent->InitAbilityActorInfo(PS, this);
	}*/
}

void ARPGPlayerCharacter::InputAbilitySystemInputTagPressed(FGameplayTag InputTag)
{
	AbilitySystemComponent->AbilityInputTagPressed(InputTag);
}

void ARPGPlayerCharacter::InputAbilitySystemInputTagReleased(FGameplayTag InputTag)
{
	AbilitySystemComponent->AbilityInputTagReleased(InputTag);
}