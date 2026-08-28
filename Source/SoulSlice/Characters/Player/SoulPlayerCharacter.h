#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Characters/SoulCharacterBase.h"
#include "SoulPlayerCharacter.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class SOULSLICE_API ASoulPlayerCharacter : public ASoulCharacterBase
{
	GENERATED_BODY()

public:
	ASoulPlayerCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;
	FORCEINLINE class USoulCombatComponent* GetCombatComponent() const {return CombatComponent;}
	
protected:
	
	// Components
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<class UCameraComponent> CameraComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<class USpringArmComponent> SpringArmComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<class USoulCombatComponent> CombatComponent;
	
	// Inputs
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inputs")
	UInputMappingContext* MappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inputs")
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inputs")
	UInputAction* LookAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inputs")
	UInputAction* EquipWeaponAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inputs")
	UInputAction* UnequipWeaponAction;
	
	// Input functions
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void EquipWeapon();
	void UnequipWeapon();
	
private:
	
	// Camera rotation sensitivity 
	
	UPROPERTY(EditAnywhere, Category = "Camera")
	float LookSensitivity = 1.0f;
};
