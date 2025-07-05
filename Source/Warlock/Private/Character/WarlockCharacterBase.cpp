// FXnRXn copyright notice


#include "Character/WarlockCharacterBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "GAS/WarlockAbilitySystemComponent.h"
#include "GAS/WarlockAttributeSet.h"

// Sets default values
AWarlockCharacterBase::AWarlockCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	WarlockAbilitySystemComponent = CreateDefaultSubobject<UWarlockAbilitySystemComponent>("Warlock Ability System Component");
	WarlockAttributeSet = CreateDefaultSubobject<UWarlockAttributeSet>("Warlock Attribute Set");
}

// Called when the game starts or when spawned
void AWarlockCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWarlockCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

