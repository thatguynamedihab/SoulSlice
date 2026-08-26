#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h" // For attribute accessors
#include "SoulAttributeSet.generated.h"
UCLASS()
class SOULSLICE_API USoulAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	USoulAttributeSet();
	
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxStamina;
	
public:
	
	ATTRIBUTE_ACCESSORS_BASIC(USoulAttributeSet, Health)
	
	ATTRIBUTE_ACCESSORS_BASIC(USoulAttributeSet, MaxHealth)
	
	ATTRIBUTE_ACCESSORS_BASIC(USoulAttributeSet, Stamina)
	
	ATTRIBUTE_ACCESSORS_BASIC(USoulAttributeSet, MaxStamina)
};