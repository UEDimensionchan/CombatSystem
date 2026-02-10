// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/Combo/AnimNotify_ComboEnd.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Component/ComboComponent.h"


void UAnimNotify_ComboEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (AActor* InActor = MeshComp->GetOwner())
	{
		if (ACharacter* InCharacter = Cast<ACharacter>(InActor))
		{
			if (UComboComponent* ComboComponent = Cast<UComboComponent>(InActor->GetComponentByClass(UComboComponent::StaticClass())))
			{
				ComboComponent->GetCombo().UpdateTheCurrentIndex();
			}
			InCharacter->StopAnimMontage();
		}
	}
}
