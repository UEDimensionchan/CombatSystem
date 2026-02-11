// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState/Tools/AnimNotifyState_StopInput.h"
#include "GameFramework/Character.h"


UAnimNotifyState_StopInput::UAnimNotifyState_StopInput()
	: bIgnoreMoveInput(true)
	, bIgnoreLookInput(false)
{

}


void UAnimNotifyState_StopInput::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (MeshComp->GetOwner())
	{
		if (ACharacter* CA = Cast<ACharacter>(MeshComp->GetOwner()))
		{
			if (AController* CL = CA->GetController())
			{
				CL->SetIgnoreMoveInput(bIgnoreMoveInput);
				CL->SetIgnoreLookInput(bIgnoreLookInput);
			}
		}
	}
}

void UAnimNotifyState_StopInput::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (MeshComp->GetOwner())
	{
		if (ACharacter* CA = Cast<ACharacter>(MeshComp->GetOwner()))
		{
			if (AController* CL = CA->GetController())
			{
				CL->SetIgnoreMoveInput(false);
				CL->SetIgnoreLookInput(false);
			}
		}
	}
}
