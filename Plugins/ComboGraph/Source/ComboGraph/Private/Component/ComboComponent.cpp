// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ComboComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayAbilitySpecHandle.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UComboComponent::UComboComponent()
	: RegisterPressTime(0.f)
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

	if (Lv_PressintervalTime > 0)
	{
		Lv_PressintervalTime -= DeltaTime;
	}

	// ...
}


void UComboComponent::Press_OnLocal(TArray<FGameplayTag> InGameplayTag, FGameplayAbilitySpecHandle InActiveHandle)
{
	if (Lv_PressintervalTime <= 0.f)
	{
		Lv_PressintervalTime = PressintervalTime;


		if (GetOwner() && InActiveHandle.IsValid())
		{
			if (UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner()))
			{
				ASC->TryActivateAbility(InActiveHandle);
			}
		}
		else if (GetOwner() && !InGameplayTag.IsEmpty())
		{
			for (FGameplayTag TG : InGameplayTag)
			{
				if (TG.IsValid())
				{
					FGameplayEventData InData;
					UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner(), TG, InData);
				}
			}
		}

		if (GetWorld())
		{
			GetWorld()->GetTimerManager().ClearTimer(ResetTimer);
		}

		Press_OnServer();
	}
}

void UComboComponent::ApplyComboTags(FGameplayTag AddTag, FGameplayTag RemoveTag)
{
	if (UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner()))
	{
		if (AddTag.IsValid())    ASC->AddLooseGameplayTag(AddTag);
		if (RemoveTag.IsValid()) ASC->RemoveLooseGameplayTag(RemoveTag);
	}
}


void UComboComponent::Press_OnServer_Implementation()
{
	Combo.SetIsPressed(true);
}

void UComboComponent::Release_OnServer_Implementation()
{
	Combo.SetIsPressed(false);
}

void UComboComponent::EndReset()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(
			ResetTimer,
			this,
			&UComboComponent::ResetCombo,
			GetCombo().GetResetTime(),
			false
		);
	}
}

void UComboComponent::ResetCombo_Implementation()
{
	Combo.ResetAllData();
}



//************FCombostruct************//
FCombostruct::FCombostruct()
{
	bIsPressed = false;
	bCanUpdate = false;
	ResetTime = 0.2;
	CurrentSection = FName(TEXT("None"));
}
void FCombostruct::UpdateTheCurrentSection()
{
	if (bCanUpdate)
	{
		bCanUpdate = false;
	}
	else
	{
		CurrentSection = FName(TEXT("None"));
	}
}
void FCombostruct::ResetAllData()
{
	bCanUpdate = false;
	bIsPressed = false;
	ResetTime = 0.2;
	CurrentSection = FName(TEXT("None"));
}
//************FCombostruct************//