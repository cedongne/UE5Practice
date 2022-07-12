// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UE5Practice.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class UE5PRACTICE_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:

	enum class EControlMode {
		SHOULDERVIEW,
		QUARTERVIEW
	};

	void SetControlMode(EControlMode ControlMode);
	EControlMode CurrentControlMode = EControlMode::SHOULDERVIEW;
	FVector DirectionToMove = FVector::ZeroVector;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;

private:
	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);
	void LookUp(float NewAxisValue);
	void Turn(float NewAxisValue);

};
