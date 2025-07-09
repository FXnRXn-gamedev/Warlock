// FXnRXn copyright notice

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "WarlockAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class UWarlockAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void ApplyInitialEffects();

private:
	UPROPERTY(EditDefaultsOnly, Category = "--- Gameplay Effects ---")
	TArray<TSubclassOf<UGameplayEffect>> InitialEffects;
	
};
