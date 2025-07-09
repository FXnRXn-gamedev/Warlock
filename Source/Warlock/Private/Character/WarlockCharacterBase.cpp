// FXnRXn copyright notice


#include "Character/WarlockCharacterBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "GAS/WarlockAbilitySystemComponent.h"
#include "GAS/WarlockAttributeSet.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/OverHeadStatsGauge.h"

// Sets default values
AWarlockCharacterBase::AWarlockCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	WarlockAbilitySystemComponent = CreateDefaultSubobject<UWarlockAbilitySystemComponent>("Warlock Ability System Component");
	WarlockAttributeSet = CreateDefaultSubobject<UWarlockAttributeSet>("Warlock Attribute Set");
	OverHeadWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverHead Widget Component"));
	OverHeadWidgetComponent->SetupAttachment(GetRootComponent());
}

void AWarlockCharacterBase::ServerSideInit()
{
	WarlockAbilitySystemComponent->InitAbilityActorInfo(this, this);
	WarlockAbilitySystemComponent->ApplyInitialEffects();
}

void AWarlockCharacterBase::ClientSideInit()
{
	WarlockAbilitySystemComponent->InitAbilityActorInfo(this, this);
}

bool AWarlockCharacterBase::IsLocallyControlledByPlayer() const
{
	
	return GetController() && GetController()->IsLocalPlayerController();
}

void AWarlockCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (NewController && !NewController->IsPlayerController())
	{
		ServerSideInit();
	}
}

// Called when the game starts or when spawned
void AWarlockCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	ConfigureOverHeadStatusWidget();
}



// Called to bind functionality to input
void AWarlockCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* AWarlockCharacterBase::GetAbilitySystemComponent() const
{
	return WarlockAbilitySystemComponent;
}

void AWarlockCharacterBase::ConfigureOverHeadStatusWidget()
{
	if (!OverHeadWidgetComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("OverHeadWidgetComponent not found"));
		return;
	}

	if (IsLocallyControlledByPlayer())
	{
		OverHeadWidgetComponent->SetHiddenInGame(true);
		return;
	}
	
	UOverHeadStatsGauge* OverHeadStatsGauge = Cast<UOverHeadStatsGauge>(OverHeadWidgetComponent->GetUserWidgetObject());
	if (OverHeadStatsGauge)
	{
		OverHeadStatsGauge->ConfigureWithASC(GetAbilitySystemComponent());
		OverHeadWidgetComponent->SetHiddenInGame(false);
		GetWorldTimerManager().ClearTimer(TimerHandle_OverHeadStatusWidgetVisibility);
		GetWorldTimerManager().SetTimer(TimerHandle_OverHeadStatusWidgetVisibility,
			this,
			&AWarlockCharacterBase::UpdateOverHeadStatusWidgetVisibility,
			OverHeadStatusWidgetVisibilityCheckUpdateGap,
			true);
	}
}

void AWarlockCharacterBase::UpdateOverHeadStatusWidgetVisibility()
{
	APawn* LocalPlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (LocalPlayerPawn)
	{
		float DistSquared = FVector::DistSquared(GetActorLocation(), LocalPlayerPawn->GetActorLocation());
		OverHeadWidgetComponent->SetHiddenInGame(DistSquared > OverHeadStatusWidgetVisibilityRangeSquared);
	}
	
}

