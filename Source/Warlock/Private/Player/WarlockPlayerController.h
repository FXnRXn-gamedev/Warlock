// FXnRXn copyright notice

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WarlockPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class AWarlockPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Only call on the server
	virtual void OnPossess(APawn* NewPawn) override;
	//Only call on the client
	virtual void AcknowledgePossession(APawn* NewPawn) override;
private:
	void SpawnGameplayWidget();
private:
	UPROPERTY()
	class AWarlockPlayerCharacter* WarlockPlayerCharacter;

	UPROPERTY(EditDefaultsOnly, Category = "--- UI ---")
	TSubclassOf<class UGameplayWidget> GameplayWidgetClass;

	UPROPERTY()
	class UGameplayWidget* GameplayWidget;
};
