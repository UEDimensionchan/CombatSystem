// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_FallingForce.generated.h"

/**
 * 
 */
UCLASS()
class COMBOGRAPH_API UAnimNotifyState_FallingForce : public UAnimNotifyState
{
	GENERATED_BODY()
	
	UAnimNotifyState_FallingForce();

protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FallingForce")
	bool bClearXYSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FallingForce")
	float FallingAddForce;
};
