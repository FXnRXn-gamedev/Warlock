// FXnRXn copyright notice

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "WarlockAttributeSet.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
UCLASS()
class UWarlockAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	ATTRIBUTE_ACCESSORS(UWarlockAttributeSet, Health)
	ATTRIBUTE_ACCESSORS(UWarlockAttributeSet, MaxHealth)
	ATTRIBUTE_ACCESSORS(UWarlockAttributeSet, Mana)
	ATTRIBUTE_ACCESSORS(UWarlockAttributeSet, MaxMana)
	
private:
	UPROPERTY()
	FGameplayAttributeData Health;

	UPROPERTY()
	FGameplayAttributeData MaxHealth;

	UPROPERTY()
	FGameplayAttributeData Mana;

	UPROPERTY()
	FGameplayAttributeData MaxMana;
};
