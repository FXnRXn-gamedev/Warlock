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

	//-- Networking --
	void ServerSideInit();
	void ClientSideInit();
	bool IsLocallyControlledByPlayer() const;
	//Only call in server to update Widget info of AI
	virtual void PossessedBy(AController* NewController) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//------------------------------------------------------------------------------------------------------------------
	//--											GAMEPLAY ABILITY												  --
	//------------------------------------------------------------------------------------------------------------------

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

private:
	UPROPERTY(VisibleDefaultsOnly , Category = "--- Gameplay Ability ---")
	class UWarlockAbilitySystemComponent*	WarlockAbilitySystemComponent;

	UPROPERTY()
	class UWarlockAttributeSet*				WarlockAttributeSet;

	//------------------------------------------------------------------------------------------------------------------
	//--											GAME UI															  --
	//------------------------------------------------------------------------------------------------------------------
private:
	UPROPERTY(VisibleDefaultsOnly , Category = "--- UI ---")
	class UWidgetComponent*					OverHeadWidgetComponent;

	void ConfigureOverHeadStatusWidget();

	UPROPERTY(VisibleDefaultsOnly , Category = "--- UI ---")
	float OverHeadStatusWidgetVisibilityCheckUpdateGap = 1.f;

	UPROPERTY(EditDefaultsOnly , Category = "--- UI ---")
	float OverHeadStatusWidgetVisibilityRangeSquared = 10000000.f;
	
	FTimerHandle TimerHandle_OverHeadStatusWidgetVisibility;
	void UpdateOverHeadStatusWidgetVisibility();
};

