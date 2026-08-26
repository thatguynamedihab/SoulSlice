#include "SoulPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


ASoulPlayerCharacter::ASoulPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	// Initialize Spring Arm Component
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	
	// Initialize Camera Component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	
	// Initialize default camera settings
	SpringArmComponent->TargetArmLength = 300.0f; // Distance from the character
	SpringArmComponent->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f)); // Angle of the camera
	
}

void ASoulPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASoulPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASoulPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

