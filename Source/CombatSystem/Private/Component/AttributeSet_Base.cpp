// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/AttributeSet_Base.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"   
#include "AbilitySystemComponent.h"

#define CHECK_OWNING_ASC_GAMEPLAYATTRIBUTE_REPNOTIFY(ClassName, PropertyName, OldValue,String)\
if (GetOwningAbilitySystemComponent())\
{\
	GAMEPLAYATTRIBUTE_REPNOTIFY(ClassName, PropertyName, OldValue);}\
else\
{\
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, String);\
}


UAttributeSet_Base::UAttributeSet_Base()
	: Super()
	, Health(100.f)
	, MaxHealth(100.f)
{

}

bool UAttributeSet_Base::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	return Super::PreGameplayEffectExecute(Data);
}

void UAttributeSet_Base::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}

void UAttributeSet_Base::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		Health = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
}

void UAttributeSet_Base::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UAttributeSet_Base, Health);
	DOREPLIFETIME(UAttributeSet_Base, MaxHealth);

}

void UAttributeSet_Base::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	CHECK_OWNING_ASC_GAMEPLAYATTRIBUTE_REPNOTIFY(
		UAttributeSet_Base, Health, OldValue,
		TEXT("OnRep_Health Error"));
}

void UAttributeSet_Base::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	CHECK_OWNING_ASC_GAMEPLAYATTRIBUTE_REPNOTIFY(
		UAttributeSet_Base, MaxHealth, OldValue,
		TEXT("OnRep_MaxHealth Error"));
}
