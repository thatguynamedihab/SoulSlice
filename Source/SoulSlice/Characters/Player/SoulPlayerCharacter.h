#pragma once

#include "CoreMinimal.h"
#include "Characters/SoulCharacterBase.h"
#include "SoulPlayerCharacter.generated.h"

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
	
protected:
	
	// Components
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<class UCameraComponent> CameraComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<class USpringArmComponent> SpringArmComponent;
};
