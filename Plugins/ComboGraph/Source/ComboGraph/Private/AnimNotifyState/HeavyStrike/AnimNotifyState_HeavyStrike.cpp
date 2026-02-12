// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState/HeavyStrike/AnimNotifyState_HeavyStrike.h"
#include "Component/ComboComponent.h"
#include "GameplayAbilitySpecHandle.h"

UAnimNotifyState_HeavyStrike::UAnimNotifyState_HeavyStrike()
	: HeavyStrikePressTime(0.3f)
{

}


void UAnimNotifyState_HeavyStrike::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (MeshComp->GetOwner())
	{
		if (UComboComponent* CC = MeshComp->GetOwner()->GetComponentByClass<UComboComponent>())
		{
			if (CC->GetRegisterPressTime() > HeavyStrikePressTime && CC->GetCombo().GetIsPressed())
			{
				TArray<FGameplayTag> TagArray;
				TagArray.Add(HeavyStrikeTag);
				CC->Press_OnLocal(TagArray, FGameplayAbilitySpecHandle());
			}
		}
	}
}
