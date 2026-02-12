// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/Combo/AnimNotify_ComboEnd.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Component/ComboComponent.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemInterface.h"
#include "GameplayPrediction.h"

UAnimNotify_ComboEnd::UAnimNotify_ComboEnd()
{
	NextSectionName = FName(TEXT("None"));
	ResetTime = 0.2;
}


void UAnimNotify_ComboEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);


	if (IAbilitySystemInterface* InAbilitySystemInterface = Cast<IAbilitySystemInterface>(MeshComp->GetOwner()))
	{
		FScopedPredictionWindow NewScopedWindow(InAbilitySystemInterface->GetAbilitySystemComponent(), true);

		if (AActor* InActor = MeshComp->GetOwner())
		{
			if (ACharacter* InCharacter = Cast<ACharacter>(InActor))
			{
				if (UComboComponent* ComboComponent = InActor->GetComponentByClass<UComboComponent>())
				{
					ComboComponent->GetCombo().SetCurrentSection(NextSectionName);
					ComboComponent->GetCombo().SetResetTime(ResetTime);

					ComboComponent->GetCombo().UpdateTheCurrentSection();

					ComboComponent->EndReset();

					ComboComponent->ApplyComboTags(ActiveTags, DisActiveTags);
				}
				InCharacter->StopAnimMontage();

			}
		}
	}
}
