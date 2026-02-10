// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState/Combo/AnimNotifyState_Combo.h"
#include "GameFramework/Actor.h"
#include "Component/ComboComponent.h"

void UAnimNotifyState_Combo::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (AActor* InActor = MeshComp->GetOwner())
	{
		if (UComboComponent* ComboComponent = Cast<UComboComponent>(InActor->GetComponentByClass(UComboComponent::StaticClass())))
		{
			if (ComboComponent->GetCombo().GetIsPressed())
			{
				ComboComponent->GetCombo().SetCanUpdate(true);
			}
		}
	}
}
