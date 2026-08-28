#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class USoundBase;
class UNiagaraComponent;

UCLASS()
class SOULSLICE_API AItemBase : public AActor
{
	GENERATED_BODY()

public:
	AItemBase();

protected:
	virtual void BeginPlay() override;
	
	// Components
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	TObjectPtr<USceneComponent> ItemRoot;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	TObjectPtr<UStaticMeshComponent> ItemMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	TObjectPtr<USphereComponent> ItemSphereCollision;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item | Sound")
	TObjectPtr<USoundBase> PickupSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item | VFX")
	TObjectPtr<UNiagaraComponent> ItemVFX;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	float PickupRadius = 50.0f;
	
	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
	
	UFUNCTION()
	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);
	
public:
};
