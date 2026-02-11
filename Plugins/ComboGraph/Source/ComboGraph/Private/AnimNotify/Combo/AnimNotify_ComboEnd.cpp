// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/Combo/AnimNotify_ComboEnd.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Component/ComboComponent.h"


UAnimNotify_ComboEnd::UAnimNotify_ComboEnd()
{
	NextSectionName = FName(TEXT("None"));
	ResetTime = 0.2;
}


void UAnimNotify_ComboEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (AActor* InActor = MeshComp->GetOwner())
	{
		if (ACharacter* InCharacter = Cast<ACharacter>(InActor))
		{
			if (UComboComponent* ComboComponent = Cast<UComboComponent>(InActor->GetComponentByClass(UComboComponent::StaticClass())))
			{
				ComboComponent->GetCombo().SetCurrentSection(NextSectionName);
				ComboComponent->GetCombo().SetResetTime(ResetTime);

				ComboComponent->GetCombo().UpdateTheCurrentSection();
			}
			InCharacter->StopAnimMontage();
		}
	}
}
