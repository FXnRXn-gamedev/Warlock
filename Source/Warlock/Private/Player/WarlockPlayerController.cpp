// FXnRXn copyright notice


#include "Player/WarlockPlayerController.h"
#include "WarlockPlayerCharacter.h"
#include "Widgets/GameplayWidget.h"

void AWarlockPlayerController::OnPossess(APawn* NewPawn)
{
	Super::OnPossess(NewPawn);

	WarlockPlayerCharacter = Cast<AWarlockPlayerCharacter>(NewPawn);
	if (WarlockPlayerCharacter)
	{
		WarlockPlayerCharacter->ServerSideInit();
	}
}

void AWarlockPlayerController::AcknowledgePossession(APawn* NewPawn)
{
	Super::AcknowledgePossession(NewPawn);

	WarlockPlayerCharacter = Cast<AWarlockPlayerCharacter>(NewPawn);
	if (WarlockPlayerCharacter)
	{
		WarlockPlayerCharacter->ClientSideInit();
		SpawnGameplayWidget();
	}
	
}

void AWarlockPlayerController::SpawnGameplayWidget()
{
	if (!IsLocalPlayerController()) return;

	GameplayWidget = CreateWidget<UGameplayWidget>(this, GameplayWidgetClass);
	if (GameplayWidget)
	{
		GameplayWidget->AddToViewport();
	}
}
