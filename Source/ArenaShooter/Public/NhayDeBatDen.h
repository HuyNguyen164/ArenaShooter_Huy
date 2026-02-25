#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NhayDeBatDen.generated.h"

class ACharacter;
class UMaterialParameterCollection;
class UMaterialParameterCollectionInstance;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARENASHOOTER_API UNhayDeBatDen : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNhayDeBatDen();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:

	UPROPERTY(EditAnywhere)
	float MaxJumpHeight = 100.f; // 1m

	UPROPERTY(EditAnywhere)
	float MaxEmissive = 10.f;
	
	UPROPERTY()
	ACharacter* OwnerCharacter;
	
	UPROPERTY(EditAnywhere)
	UMaterialParameterCollection* MPC_Jumping;
	
	UPROPERTY()
	UMaterialParameterCollectionInstance* MPC_Instance;
	
	float CurrentEmissive = 0.f;
};
