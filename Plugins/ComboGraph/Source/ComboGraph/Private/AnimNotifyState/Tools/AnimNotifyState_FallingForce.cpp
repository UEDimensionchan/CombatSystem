// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState/Tools/AnimNotifyState_FallingForce.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


UAnimNotifyState_FallingForce::UAnimNotifyState_FallingForce()
	: bClearXYSpeed(false)
	, FallingAddForce(-1000000.f)
{

}


void UAnimNotifyState_FallingForce::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (MeshComp->GetOwner())
	{
		if (ACharacter* CA = Cast<ACharacter>(MeshComp->GetOwner()))
		{
			CA->GetCharacterMovement()->Velocity.X = 0;
			CA->GetCharacterMovement()->Velocity.Y = 0;
		}
	}

}

void UAnimNotifyState_FallingForce::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (MeshComp->GetOwner())
	{
		if (ACharacter* CA = Cast<ACharacter>(MeshComp->GetOwner()))
		{
			CA->GetCharacterMovement()->AddForce(FVector(0.f, 0.f, FallingAddForce));
			CA->GetCharacterMovement()->Velocity.X = 0;
			CA->GetCharacterMovement()->Velocity.Y = 0;
		}
	}
}

void UAnimNotifyState_FallingForce::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (MeshComp->GetOwner())
	{
		if (ACharacter* CA = Cast<ACharacter>(MeshComp->GetOwner()))
		{
			CA->GetCharacterMovement()->ClearAccumulatedForces();
		}
	}
}
