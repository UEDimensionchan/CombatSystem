// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "CombatCharacter.generated.h"

class UAbilityComponent;
class UAttributeSet_Base;
class UGameplayAbility;
struct FGameplayAbilitySpecHandle;

UCLASS()
class COMBATSYSTEM_API ACombatCharacter : public ACharacter , public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACombatCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	TArray<FGameplayAbilitySpecHandle> InitGrantAbilities(TArray<TSubclassOf<UGameplayAbility>> InAbilities);


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> GrantAbilities;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAbilityComponent> AbilityComponent;
	TObjectPtr<UAttributeSet_Base> AttributeSet;
};
