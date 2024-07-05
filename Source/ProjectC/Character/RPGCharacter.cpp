#include "RPGCharacter.h"
#include "AbilitySystem/RPGAbilitySystemComponent.h"
#include "AbilitySystem/RPGAttributeSet.h"
#include "AbilitySystem/Abilities/RPGGameplayAbility.h"
#include "Player/RPGEnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Player/RPGPlayerState.h"

// Sets default values
ARPGCharacter::ARPGCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bAllowTickOnDedicatedServer = true;

	OverrideInputComponentClass = URPGEnhancedInputComponent::StaticClass();
}

void ARPGCharacter::InitializeAttributes()
{
	if (AbilitySystemComponent)
	{
		FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);

		for (auto Effect : DefaultEffects)
		{
			FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(Effect, 1, EffectContextHandle);
			if (EffectSpecHandle.IsValid())
			{
				FActiveGameplayEffectHandle EffectHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
			}
		}
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHPAttribute()).AddUObject(this, &ARPGCharacter::HPChanged);
	}
}

void ARPGCharacter::GiveAbilities()
{
	if (HasAuthority() && AbilitySystemComponent)
	{
		for (auto Ability : Abilities)
		{
			URPGGameplayAbility* AbilityCDO = Ability->GetDefaultObject<URPGGameplayAbility>();
			FGameplayAbilitySpec AbilitySpec(AbilityCDO, 1);
			AbilitySpec.SourceObject = this;
			AbilitySpec.DynamicAbilityTags.AddTag(AbilityCDO->AbilityInputTag);

			//AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, static_cast<int32>(Ability.GetDefaultObject()->AbilityInputID), this));
			AbilitySystemComponent->GiveAbility(AbilitySpec);
		}
	}
}

void ARPGCharacter::HPChanged(const FOnAttributeChangeData& Data)
{
	float HP = Data.NewValue;
	UE_LOG(LogTemp, Warning, TEXT("HP Change : %f"), HP);

}
void ARPGCharacter::UpdateHP(const float NewHP)
{
}

void ARPGCharacter::AttackToTarget(ARPGCharacter* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetASC = Target->GetAbilitySystemComponent();
	if (TargetASC)
	{
		checkf(GameplayEffectClass, TEXT("EffectClass is invalid"));

		FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);
		const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle);
		TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	}
}

// Called when the game starts or when spawned
void ARPGCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARPGCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	ARPGPlayerState* PS = GetPlayerState<ARPGPlayerState>();
	if (PS)
	{
		AbilitySystemComponent = Cast<URPGAbilitySystemComponent>(PS->GetAbilitySystemComponent());
		AbilitySystemComponent->InitAbilityActorInfo(PS, this);
		AttributeSet = PS->GetAttributeSet();

		InitializeAttributes();
		GiveAbilities();
	}
}

void ARPGCharacter::OnRep_PlayerState()
{
	ARPGPlayerState* PS = GetPlayerState<ARPGPlayerState>();
	if (PS)
	{
		AbilitySystemComponent = Cast<URPGAbilitySystemComponent>(PS->GetAbilitySystemComponent());
		AbilitySystemComponent->InitAbilityActorInfo(PS, this);
	}
}

void ARPGCharacter::InputAbilitySystemInputTagPressed(FGameplayTag InputTag)
{
	AbilitySystemComponent->AbilityInputTagPressed(InputTag);
}

void ARPGCharacter::InputAbilitySystemInputTagReleased(FGameplayTag InputTag)
{
	AbilitySystemComponent->AbilityInputTagReleased(InputTag);
}

// Called every frame
void ARPGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARPGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
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
		PEI->BindAbilityActions(InputConfig, this, &ARPGCharacter::InputAbilitySystemInputTagPressed, &ARPGCharacter::InputAbilitySystemInputTagReleased, BindHandles);
	}
}

UAbilitySystemComponent* ARPGCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

