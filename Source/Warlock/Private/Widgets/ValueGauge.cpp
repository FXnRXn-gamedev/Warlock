// FXnRXn copyright notice


#include "Widgets/ValueGauge.h"

#include "AbilitySystemComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UValueGauge::NativePreConstruct()
{
	Super::NativePreConstruct();

	ProgressBar->SetFillColorAndOpacity(BarColor);
}

void UValueGauge::SetAndBoundToGameplayAttribute(class UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayAttribute& Attribute, const FGameplayAttribute& MaxAttribute)
{
	if (AbilitySystemComponent)
	{
		bool bFound;
		float Value = AbilitySystemComponent->GetGameplayAttributeValue(Attribute, bFound);
		float MaxValue = AbilitySystemComponent->GetGameplayAttributeValue(MaxAttribute, bFound);
		if (bFound)
		{
			SetValue(Value, MaxValue);
		}

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(this, &UValueGauge::ValueChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MaxAttribute).AddUObject(this, &UValueGauge::MaxValueChanged);
	}
	
	
}

void UValueGauge::SetValue(float NewValue, float MaxValue)
{

	CachedVal = NewValue;
	CachedMaxVal = MaxValue;
	
	if (MaxValue == 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Value Gauge: %s, MaxValue can't be 0"), *GetName());
		return;
	}
	
	float Percent = NewValue / MaxValue;
	ProgressBar->SetPercent(Percent);
	FNumberFormattingOptions FormatOps = FNumberFormattingOptions().SetMaximumFractionalDigits(0);
	
	ValueText->SetText
	(FText::Format(
		FText::FromString("{0}/{1}"),
		FText::AsNumber(NewValue, &FormatOps),
		FText::AsNumber(MaxValue, &FormatOps)
		));
}

void UValueGauge::ValueChanged(const FOnAttributeChangeData& ChangedData)
{
	SetValue(ChangedData.NewValue, CachedMaxVal);
}

void UValueGauge::MaxValueChanged(const FOnAttributeChangeData& ChangedData)
{
	SetValue(CachedVal, ChangedData.NewValue);
}
