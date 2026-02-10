// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbility_MeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class COMBOGRAPH_API UGameplayAbility_MeleeAttack : public UGameplayAbility
{
	GENERATED_BODY()

	UGameplayAbility_MeleeAttack();
	
protected:
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;


	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION()
	void MontageEnd();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo")
	UAnimMontage* ComboMontage;

};
