#include "NhayDeBatDen.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UNhayDeBatDen::UNhayDeBatDen()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UNhayDeBatDen::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	
	if (!OwnerCharacter) return;
	
	if (MPC_Jumping)
	{
		MPC_Instance = GetWorld()->GetParameterCollectionInstance(MPC_Jumping);
	}
}

// Called every frame
void UNhayDeBatDen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (!OwnerCharacter || !MPC_Instance) return;

	if (!OwnerCharacter->GetCharacterMovement()->IsFalling())
	{
		MPC_Instance->SetScalarParameterValue(FName("Emissive"), 0.f);
		return;
	}

	FVector Start = OwnerCharacter->GetActorLocation();
	FVector End = Start - FVector(0, 0, 1000.f);

	FHitResult Hit;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(OwnerCharacter);

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		Hit,
		Start,
		End,
		ECC_Visibility,
		Params
	);

	if (bHit)
	{
		float Distance = Start.Z - Hit.Location.Z;

		float Alpha = FMath::Clamp(Distance / MaxJumpHeight, 0.f, 1.f);

		float EmissiveValue = Alpha * MaxEmissive;

		MPC_Instance->SetScalarParameterValue(FName("Emissive"), EmissiveValue);
	}
}

