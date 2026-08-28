#include "SoulCombatComponent.h"
#include "Items/Weapons/WeaponBase.h"
#include "Characters/SoulCharacterBase.h"

USoulCombatComponent::USoulCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USoulCombatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USoulCombatComponent::SetNearbyWeapon(AItemBase* Item)
{
	NearbyItem = Item;
}

void USoulCombatComponent::EquipNearbyWeapon()
{
	AWeaponBase* Weapon = Cast<AWeaponBase>(NearbyItem);
	ASoulCharacterBase* Character = Cast<ASoulCharacterBase>(GetOwner());

	if (!Weapon || !Character)
	{
		return;
	}

	Weapon->AttachToCharacter(Character);

	EquippedWeapon = Weapon;
	NearbyItem = nullptr;
}

void USoulCombatComponent::UnequipWeapon()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->DetachFromCharacter();
		EquippedWeapon = nullptr;
	}
}


