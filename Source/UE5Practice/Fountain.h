#pragma once

#include "UE5Practice.h"
#include "GameFramework/Actor.h"
#include "Fountain.generated.h"

UCLASS()
class UE5PRACTICE_API AFountain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFountain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type) override;
	virtual void PostInitializeComponents() override;

	virtual void Tick(float DeltaTime) override;

public:	
	// Called every frame

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent *Body;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent *Water;

	UPROPERTY(VisibleAnywhere)
	UPointLightComponent *Light;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent * Splash;

	UPROPERTY(EditAnywhere, Category = "ID")
	int32 ID;

	int32 count;

};
