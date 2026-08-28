#include "ItemBase.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraComponent.h"
#include "Components/Combat/SoulCombatComponent.h"


AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	// Initialize Components and configure their properties
	
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	SetRootComponent(ItemMesh);
	ItemMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ItemSphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ItemSphereCollision"));
	ItemSphereCollision->SetupAttachment(ItemMesh);
	ItemSphereCollision->SetSphereRadius(PickupRadius);
	ItemSphereCollision->SetGenerateOverlapEvents(true);
	
	ItemVFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ItemVFX"));
	ItemVFX->SetupAttachment(ItemMesh);
	
}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
	ItemSphereCollision->OnComponentBeginOverlap.AddDynamic(
		this,
		&AItemBase::OnSphereBeginOverlap);

	ItemSphereCollision->OnComponentEndOverlap.AddDynamic(
		this,
		&AItemBase::OnSphereEndOverlap);
}

void AItemBase::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor) return;;
	
	USoulCombatComponent* CombatComponent = OtherActor->FindComponentByClass<USoulCombatComponent>();
	if (CombatComponent)
	{
		CombatComponent->SetNearbyWeapon(this);
	}
}

void AItemBase::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor) return;
	
	USoulCombatComponent* CombatComponent = OtherActor->FindComponentByClass<USoulCombatComponent>();
	if (CombatComponent)
	{
		CombatComponent->SetNearbyWeapon(nullptr);
	}
}
