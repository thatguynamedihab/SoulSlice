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
	ASoulPlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;
	
protected:
	
	// Components
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<class UCameraComponent> CameraComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<class USpringArmComponent> SpringArmComponent;
	
	// Inputs
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inputs")
	UInputMappingContext* MappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inputs")
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inputs")
	UInputAction* LookAction;
	
	// Input functions
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	
private:
	
	// Camera rotation sensitivity 
	
	UPROPERTY(EditAnywhere, Category = "Camera")
	float LookSensitivity = 1.0f;
};
