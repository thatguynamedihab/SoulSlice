#include "SoulMovementComponent.h"

#include "Engine/DamageEvents.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "Math/RotationMatrix.h"

void USoulMovementComponent::Move(const FVector2D& MovementInput)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;
	
	AController* Controller = Character->GetController();
	if (!Controller) return;
	
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	Character->AddMovementInput(ForwardDirection, MovementInput.Y);
	Character->AddMovementInput(RightDirection, MovementInput.X);
}


