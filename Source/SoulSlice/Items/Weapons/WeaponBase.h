#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Items/ItemBase.h"
#include "WeaponBase.generated.h"

class ASoulCharacterBase;

UCLASS()
class SOULSLICE_API AWeaponBase : public AItemBase
{
	GENERATED_BODY()

public:
	AWeaponBase();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName EquipSocketName;

public:
	void AttachToCharacter(ASoulCharacterBase* Character);
	void DetachFromCharacter();
};
