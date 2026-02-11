// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_StopInput.generated.h"

/**
 * 
 */
UCLASS()
class COMBOGRAPH_API UAnimNotifyState_StopInput : public UAnimNotifyState
{
	GENERATED_BODY()

	UAnimNotifyState_StopInput();
	
protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StopInput")
	bool bIgnoreMoveInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StopInput")
	bool bIgnoreLookInput;
	

};
