// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ComboComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayAbilitySpecHandle.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UComboComponent::UComboComponent()
	: ResetTime(0.5f)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
	// ...
}

void UComboComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, Combo);
}



// Called when the game starts
void UComboComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UComboComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UComboComponent::Press_OnLocal(FGameplayTag InGameplayTag, FGameplayAbilitySpecHandle InActiveHandle)
{
	if (GetOwner() && InActiveHandle.IsValid())
	{
		if (UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner()))
		{
			ASC->TryActivateAbility(InActiveHandle);
		}
	}
	else if (GetOwner() && InGameplayTag.IsValid())
	{
		FGameplayEventData InData;
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner(), InGameplayTag, InData);
		Press_OnServer();
	}
}

void UComboComponent::ResetCombo()
{
	Combo.ResetAllData();
}


void UComboComponent::Press_OnServer_Implementation()
{
	Combo.SetCanUpdate(true);
	Combo.SetIsPressed(true);
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(Combo.ResetTimer);
	}
}

void UComboComponent::Release_OnServer_Implementation()
{
	Combo.SetIsPressed(false);
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(
			Combo.ResetTimer,
			this,
			&UComboComponent::ResetCombo,
			ResetTime,
			false
		);
	}
}



//************FCombostruct************//
FCombostruct::FCombostruct()
{
	CurrentIndex = 0;
	MaxIndex = 0;
	bIsPressed = false;
	bCanUpdate = false;
}
void FCombostruct::UpdateTheCurrentIndex()
{
	if (bCanUpdate)
	{
		if (++CurrentIndex > MaxIndex - 1)
		{
			CurrentIndex = 0;
		}
		else
		{
			bCanUpdate = false;
		}
	}
	else
	{
		CurrentIndex = 0;
	}
}
void FCombostruct::ResetAllData()
{
	bCanUpdate = false;
	bIsPressed = false;
	CurrentIndex = 0;
}
//************FCombostruct************//