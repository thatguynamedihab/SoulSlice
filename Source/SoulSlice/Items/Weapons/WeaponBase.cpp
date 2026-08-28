#include "WeaponBase.h"
#include "Characters/SoulCharacterBase.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraComponent.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeaponBase::AttachToCharacter(ASoulCharacterBase* Character)
{
	if (!Character || !Character->GetMesh() || !ItemMesh)
	{
		return;
	}
	const FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
	ItemMesh->AttachToComponent(Character->GetMesh(), AttachmentRules, EquipSocketName);
	
	if (ItemSphereCollision)
	{
		ItemSphereCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	if (ItemVFX)
	{
		ItemVFX->Deactivate();
	}
}

void AWeaponBase::DetachFromCharacter()
{
	const FDetachmentTransformRules DetachmentRules = FDetachmentTransformRules::KeepWorldTransform;
	ItemMesh->DetachFromComponent(DetachmentRules);
	
	if(ItemSphereCollision)
	{
		ItemSphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}

	if (ItemVFX)
	{
		ItemVFX->Activate();
	}
}

