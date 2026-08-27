#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SoulMovementComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SOULSLICE_API USoulMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	void Move(const FVector2D& MovementInput);
};
