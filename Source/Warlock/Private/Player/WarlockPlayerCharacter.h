// FXnRXn copyright notice

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystemInterface.h"
#include "Character/WarlockCharacterBase.h"
#include "InputActionValue.h"
#include "WarlockPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AWarlockPlayerCharacter : public AWarlockCharacterBase
{
	GENERATED_BODY()

public:
	AWarlockPlayerCharacter();
	virtual void PawnClientRestart() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
private:
	
	#pragma region Components
	UPROPERTY(VisibleDefaultsOnly, Category = "--- View ---")
	class USpringArmComponent* SpringArm;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "--- View ---")
	class UCameraComponent* CameraComp;

	#pragma endregion 

	#pragma region InputSystem
	
	UPROPERTY(EditDefaultsOnly, Category = "--- Input ---|Action")
	class UInputAction* JumpInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "--- Input ---|Action")
	class UInputAction* LookInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "--- Input ---|Action")
	class UInputAction* MoveInputAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "--- Input ---|MappingContext")
	class UInputMappingContext* GameplayInputMappingContext;
	
	#pragma endregion

	void HandleLookInput(const FInputActionValue& InputActionValue);
	void HandleMoveInput(const FInputActionValue& InputActionValue);

	FVector GetLookRightDir() const;
	FVector GetLookForwardDir() const;
	FVector GetMoveForwardDir() const;
};
