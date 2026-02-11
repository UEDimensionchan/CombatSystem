// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ComboComponent.generated.h"

struct FGameplayTag;
struct FGameplayAbilitySpecHandle;


USTRUCT(BlueprintType)
struct FCombostruct
{
	GENERATED_BODY()

	FCombostruct();

public:
	void UpdateTheCurrentSection();
	void SetCanUpdate(bool bCanUpdateTheSection) { bCanUpdate = bCanUpdateTheSection; }
	bool GetIsPressed() { return bIsPressed; }
	void SetIsPressed(bool InIsPressed) { bIsPressed = InIsPressed; }

	void ResetAllData();

	void SetCurrentSection(FName InSection) { CurrentSection = InSection; }
	FName GetCurrentSection() const { return CurrentSection; }

	void SetResetTime(float InTime) { ResetTime = InTime; }
	float GetResetTime() { return ResetTime; }

	UPROPERTY()
	FTimerHandle ResetTimer;

private:
	UPROPERTY()
	FName CurrentSection;

	UPROPERTY()
	float ResetTime;

	UPROPERTY()
	bool bIsPressed;
	UPROPERTY()
	bool bCanUpdate;
};




UCLASS(Abstract, Blueprintable)
class COMBOGRAPH_API UComboComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UComboComponent();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	FCombostruct& GetCombo() { return Combo; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Press"),Category = "Combo")
	void Press_OnLocal(FGameplayTag InGameplayTag, FGameplayAbilitySpecHandle InActiveHandle);

	UFUNCTION(Server,Reliable)
	void Press_OnServer();

	UFUNCTION(Server, Reliable, BlueprintCallable, meta = (DisplayName = "Release"), Category = "Combo")
	void Release_OnServer();

	UFUNCTION(BlueprintCallable)
	void ResetCombo();


protected:
	UPROPERTY(Replicated)
	FCombostruct Combo;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float ResetTime;
};
