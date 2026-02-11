// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "GameplayTagContainer.h"
#include "AnimNotifyState_HeavyStrike.generated.h"

/**
 * 
 */
UCLASS()
class COMBOGRAPH_API UAnimNotifyState_HeavyStrike : public UAnimNotifyState
{
	GENERATED_BODY()

	UAnimNotifyState_HeavyStrike();
	
protected:
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeavyStrike")
	FGameplayTag HeavyStrikeTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeavyStrike")
	float HeavyStrikePressTime;
};
