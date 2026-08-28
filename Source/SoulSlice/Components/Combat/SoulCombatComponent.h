#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SoulCombatComponent.generated.h"

class AItemBase;
class AWeaponBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SOULSLICE_API USoulCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USoulCombatComponent();

protected:
	virtual void BeginPlay() override;

public:
	void SetNearbyWeapon(AItemBase* Item);
	void EquipNearbyWeapon();
	void UnequipWeapon();
	
protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<AItemBase> NearbyItem;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<AWeaponBase> EquippedWeapon;
};
