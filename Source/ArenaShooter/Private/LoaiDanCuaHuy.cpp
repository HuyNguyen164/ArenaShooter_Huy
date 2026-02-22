// Fill out your copyright notice in the Description page of Project Settings.


#include "LoaiDanCuaHuy.h"

#include "TimerManager.h"
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
	SphereCollision->SetCollisionObjectType(ECC_WorldDynamic);
	SphereCollision->SetNotifyRigidBodyCollision(true);
	// SphereCollision->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	// SphereCollision->SetNotifyRigidBodyCollision(true);
	SphereCollision->OnComponentHit.AddDynamic(this, &ALoaiDanCuaHuy::OnProjectileHit);
	
	// Set up collision properties for the sphere
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(SphereCollision);
	
	// Set up projectile movement component
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
}

// Called when the game starts or when spawned
void ALoaiDanCuaHuy::BeginPlay()
{
	Super::BeginPlay();
	
}

// void ALoaiDanCuaHuy::OnProjectileHit(
// 	UPrimitiveComponent* HitComponent,
// 	AActor* OtherActor,
// 	UPrimitiveComponent* OtherComp,
// 	FVector NormalImpulse,
// 	const FHitResult& Hit)
// {
// 	ACharacter* HitCharacter = Cast<ACharacter>(OtherActor);
// 	if (HitCharacter)
// 	{
// 		UE_LOG(LogTemp, Warning, TEXT("Hit character: %s"), *HitCharacter->GetName());
// 		USkeletalMeshComponent* MeshComponent = HitCharacter->GetMesh();
// 		if (MeshComponent)
// 		{
// 			UE_LOG(LogTemp, Warning, TEXT("Hit character mesh: %s"), *MeshComponent->GetName());
// 			UMaterialInterface* Material = MeshComponent->GetMaterial(0);
// 			if (Material)
// 			{
// 				UE_LOG(LogTemp, Warning, TEXT("Material: %s"), *Material->GetName());
// 				MeshComponent->CreateAndSetMaterialInstanceDynamic(0)->SetVectorParameterValue(
// 					FName("Paint Tint"), FLinearColor::Green);
// 			}
// 		}
// 	}
// }

void ALoaiDanCuaHuy::OnProjectileHit(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	if (!OtherActor || OtherActor == this || !HitMaterial)
		return;

	UPrimitiveComponent* TargetComponent = Hit.GetComponent();

	if (ACharacter* HitCharacter = Cast<ACharacter>(OtherActor))
	{
		TargetComponent = HitCharacter->GetMesh();
	}

	if (!TargetComponent)
		return;

	int32 MaterialCount = TargetComponent->GetNumMaterials();

	// Save original materials
	TArray<UMaterialInterface*> StoredMaterials;
	
	for (int32 i = 0; i < MaterialCount; i++)
	{
		StoredMaterials.Add(TargetComponent->GetMaterial(i));
		TargetComponent->SetMaterial(i, HitMaterial);
	}

	OriginalMaterials.Add(TargetComponent, StoredMaterials);

	if (!bHasHit)
	{
		bHasHit = true;
		SetLifeSpan(1.0f);
	}
	
	// Timer
	FTimerHandle TimerHandle;

	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		FTimerDelegate::CreateUObject(
			this,
			&ALoaiDanCuaHuy::RestoreMaterials,
			TargetComponent
		),
		0.2f,
		false
	);
}

void ALoaiDanCuaHuy::RestoreMaterials(UPrimitiveComponent* TargetComponent)
{
	if (!TargetComponent)
		return;

	if (!OriginalMaterials.Contains(TargetComponent))
		return;

	TArray<UMaterialInterface*>& StoredMaterials =
		OriginalMaterials[TargetComponent];

	for (int32 i = 0; i < StoredMaterials.Num(); i++)
	{
		TargetComponent->SetMaterial(i, StoredMaterials[i]);
	}

	OriginalMaterials.Remove(TargetComponent);
}

// Called every frame
void ALoaiDanCuaHuy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

