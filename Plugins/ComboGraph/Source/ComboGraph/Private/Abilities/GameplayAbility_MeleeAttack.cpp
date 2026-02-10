// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GameplayAbility_MeleeAttack.h"
#include "Component/ComboComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"

UGameplayAbility_MeleeAttack::UGameplayAbility_MeleeAttack()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}


bool UGameplayAbility_MeleeAttack::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	return ComboMontage && Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

void UGameplayAbility_MeleeAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (GetAvatarActorFromActorInfo())
	{
		if (UComboComponent* ComboCom = GetAvatarActorFromActorInfo()->GetComponentByClass<UComboComponent>())
		{
			ComboCom->GetCombo().SetMaxIndex(ComboMontage->GetNumSections());

			UAbilityTask_PlayMontageAndWait* MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
				this,
				NAME_None,
				ComboMontage,
				1.f,
				FName(*FString::FromInt(ComboCom->GetComboCurrentIndex())),
				true,
				1.f,
				0.f,
				true
			);
			if (!MontageTask)
			{
				EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
				return;
			}
			MontageTask->OnCompleted.AddDynamic(this, &UGameplayAbility_MeleeAttack::MontageEnd);
			MontageTask->OnBlendOut.AddDynamic(this, &UGameplayAbility_MeleeAttack::MontageEnd);
			MontageTask->OnInterrupted.AddDynamic(this, &UGameplayAbility_MeleeAttack::MontageEnd);
			MontageTask->OnCancelled.AddDynamic(this, &UGameplayAbility_MeleeAttack::MontageEnd);

			MontageTask->ReadyForActivation();
		}
	}
}

void UGameplayAbility_MeleeAttack::MontageEnd()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}
