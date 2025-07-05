// FXnRXn copyright notice

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "WarlockCharacterBase.generated.h"

UCLASS()
class AWarlockCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWarlockCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//------------------------------------------------------------------------------------------------------------------
	//--											GAMEPLAY ABILITY												  --
	//------------------------------------------------------------------------------------------------------------------

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

private:
	UPROPERTY()
	class UWarlockAbilitySystemComponent*	WarlockAbilitySystemComponent;

	UPROPERTY()
	class UWarlockAttributeSet*				WarlockAttributeSet;

};
