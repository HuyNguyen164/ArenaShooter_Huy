// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "LoaiDanCuaHuy.generated.h"

UCLASS()
class ARENASHOOTER_API ALoaiDanCuaHuy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALoaiDanCuaHuy();
	
	UFUNCTION()
	void OnProjectileHit(
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit
	);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Collision Component
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = SphereCollision)
	USphereComponent* SphereCollision;
	
	// Static Mesh Component
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = StaticMesh)
	UStaticMeshComponent* StaticMesh;
	
	// Projectile Movement Component
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = StaticMesh)
	UProjectileMovementComponent* ProjectileMovement;

	// Material for hit effect
	UPROPERTY(EditDefaultsOnly, Category = "Hit Effect")
	UMaterialInterface* HitMaterial;
	
	// Save original materials to restore after hit effect
	TMap<TWeakObjectPtr<UPrimitiveComponent>, TArray<UMaterialInterface*>> OriginalMaterials;
	
	// Restore original materials after hit effect duration
	UFUNCTION()
	void RestoreMaterials(UPrimitiveComponent* TargetComponent);
	
private:
	bool bHasHit = false;
	//
	// FTimerHandle DestroyTimerHandle;
	//
	// void DestroyProjectile();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
