// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/CombatCharacter.h"
#include "Component/AbilityComponent.h"
#include "Component/AttributeSet_Base.h"

// Sets default values
ACombatCharacter::ACombatCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilityComponent = CreateDefaultSubobject<UAbilityComponent>(TEXT("AbilitySystemComponent"));
	AbilityComponent->SetIsReplicated(true);
	AbilityComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AbilityComponent->SetMontageRepAnimPositionMethod(ERepAnimPositionMethod::CurrentSectionId);

	AttributeSet = CreateDefaultSubobject<UAttributeSet_Base>(TEXT("AttributeSetBse"));
}

// Called when the game starts or when spawned
void ACombatCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACombatCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACombatCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* ACombatCharacter::GetAbilitySystemComponent() const
{
	return AbilityComponent;
}

TArray<FGameplayAbilitySpecHandle> ACombatCharacter::InitGrantAbilities(TArray<TSubclassOf<UGameplayAbility>> InAbilities)
{
	if (!GetAbilitySystemComponent() && !HasAuthority())
		return TArray<FGameplayAbilitySpecHandle>();

	TArray<FGameplayAbilitySpecHandle> SpecHandles;
	for (TSubclassOf<UGameplayAbility> InAbility : InAbilities)
	{
		FGameplayAbilitySpecHandle SpecHandle = GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(InAbility, 1, -1, this));
		SpecHandles.Add(SpecHandle);
	}

	return SpecHandles;
}



