// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet_Base.generated.h"


struct FAttributeDataTableBase;

#define PROPERTY_FUNCTION_REGISTRATION(ClassName, PropertyName) \
	float Last##PropertyName; \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class COMBATSYSTEM_API UAttributeSet_Base : public UAttributeSet
{
	GENERATED_BODY()

	UAttributeSet_Base();

public:
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	PROPERTY_FUNCTION_REGISTRATION(UAttributeSet_Base, Health)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	PROPERTY_FUNCTION_REGISTRATION(UAttributeSet_Base, MaxHealth)

public:
	virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);
	
};
