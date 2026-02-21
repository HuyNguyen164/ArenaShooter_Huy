// Fill out your copyright notice in the Description page of Project Settings.


#include "LoaiDanCuaHuy.h"

#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
ALoaiDanCuaHuy::ALoaiDanCuaHuy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create components
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	RootComponent = SphereCollision;
	
	SphereCollision->InitSphereRadius(15.f);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SphereCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	SphereCollision->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	// SphereCollision->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	// SphereCollision->SetNotifyRigidBodyCollision(true);
	SphereCollision->OnComponentHit.AddDynamic(this, &ALoaiDanCuaHuy::OnProjectileHit);
	
	// Set up collision properties for the sphere
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(SphereCollision);
	
	// Set up projectile movement component
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 6000.f;
	ProjectileMovement->MaxSpeed = 6000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
}

// Called when the game starts or when spawned
void ALoaiDanCuaHuy::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALoaiDanCuaHuy::OnProjectileHit(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	ACharacter* HitCharacter = Cast<ACharacter>(OtherActor);
	if (HitCharacter)
	{
		USkeletalMeshComponent* MeshComponent = HitCharacter->GetMesh();
		if (MeshComponent)
		{
			UMaterialInterface* Material = MeshComponent->GetMaterial(0);
			if (Material)
			{
				MeshComponent->CreateAndSetMaterialInstanceDynamic(0)->SetVectorParameterValue(
					TEXT("Basecolor"), FLinearColor::Green);
			}
		}
	}
}

// Called every frame
void ALoaiDanCuaHuy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

