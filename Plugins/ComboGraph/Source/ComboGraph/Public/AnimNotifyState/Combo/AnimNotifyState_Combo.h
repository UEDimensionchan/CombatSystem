// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_Combo.generated.h"

/**
 * 
 */
UCLASS()
class COMBOGRAPH_API UAnimNotifyState_Combo : public UAnimNotifyState
{
	GENERATED_BODY()

	UAnimNotifyState_Combo();
	
public:
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;

};
