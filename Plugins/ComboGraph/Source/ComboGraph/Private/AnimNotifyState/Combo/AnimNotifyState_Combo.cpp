// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState/Combo/AnimNotifyState_Combo.h"
#include "GameFramework/Actor.h"
#include "Component/ComboComponent.h"
#include "AbilitySystemInterface.h"
#include "GameplayPrediction.h"

UAnimNotifyState_Combo::UAnimNotifyState_Combo()
{
	
}

void UAnimNotifyState_Combo::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (IAbilitySystemInterface* InAbilitySystemInterface = Cast<IAbilitySystemInterface>(MeshComp->GetOwner()))
	{
		FScopedPredictionWindow NewScopedWindow(InAbilitySystemInterface->GetAbilitySystemComponent(), true);
		if (AActor* InActor = MeshComp->GetOwner())
		{
			if (UComboComponent* ComboComponent = Cast<UComboComponent>(InActor->GetComponentByClass(UComboComponent::StaticClass())))
			{
				//if (!MeshComp->GetOuter()->GetWorld()->IsNetMode(ENetMode::NM_Client))
				{
					if (ComboComponent->GetCombo().GetIsPressed() && !ComboComponent->GetCombo().GetCanUpdate())
					{
						ComboComponent->GetCombo().SetCanUpdate(true);
					}
				}
			}
		}
	}
}

void UAnimNotifyState_Combo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}
