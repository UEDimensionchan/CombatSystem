// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GameplayTagContainer.h"
#include "AnimNotify_ComboEnd.generated.h"

/**
 * 
 */
UCLASS()
class COMBOGRAPH_API UAnimNotify_ComboEnd : public UAnimNotify
{
	GENERATED_BODY()

	UAnimNotify_ComboEnd();
	
protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName NextSectionName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ResetTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag NeedActiveTags;
};
