// FXnRXn copyright notice


#include "Player/WarlockPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"


AWarlockPlayerCharacter::AWarlockPlayerCharacter()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->bUsePawnControlRotation = true;
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComp->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);
}

void AWarlockPlayerCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();
	APlayerController* OwningPlayerController = GetController<APlayerController>();
	if (OwningPlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* InputSubsystem = OwningPlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		if (InputSubsystem)
		{
			InputSubsystem->RemoveMappingContext(GameplayInputMappingContext);
			InputSubsystem->AddMappingContext(GameplayInputMappingContext,0 );
		}
	}
}

void AWarlockPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComp)
	{
		EnhancedInputComp->BindAction(JumpInputAction, ETriggerEvent::Triggered, this, &AWarlockPlayerCharacter::Jump);
		EnhancedInputComp->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &AWarlockPlayerCharacter::HandleLookInput);
		EnhancedInputComp->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &AWarlockPlayerCharacter::HandleMoveInput);
	}
	
}

void AWarlockPlayerCharacter::HandleLookInput(const FInputActionValue& InputActionValue)
{
	FVector2D InputLookVal = InputActionValue.Get<FVector2D>();

	AddControllerPitchInput(-InputLookVal.Y);
	AddControllerYawInput(InputLookVal.X);
}

void AWarlockPlayerCharacter::HandleMoveInput(const FInputActionValue& InputActionValue)
{
	FVector2D InputMoveVal = InputActionValue.Get<FVector2D>();
	InputMoveVal.Normalize();

	AddMovementInput((GetMoveForwardDir() * InputMoveVal.Y) + (GetLookRightDir() * InputMoveVal.X));
	
}

FVector AWarlockPlayerCharacter::GetLookRightDir() const
{
	return CameraComp->GetRightVector();
}

FVector AWarlockPlayerCharacter::GetLookForwardDir() const
{
	return CameraComp->GetForwardVector();
}

FVector AWarlockPlayerCharacter::GetMoveForwardDir() const
{
	return FVector::CrossProduct(GetLookRightDir(), FVector::UpVector);
}
