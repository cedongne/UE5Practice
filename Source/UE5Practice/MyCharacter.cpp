// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_MESH(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard"));
	if (SK_MESH.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SK_MESH.Object);
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> BP_ANIM_RUN(TEXT("/Game/Animations/WarriorAnimBlueprint.WarriorAnimBlueprint_C"));
	if (BP_ANIM_RUN.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(BP_ANIM_RUN.Class);
	}

	SetControlMode(EControlMode::SHOULDERVIEW);

	ArmLengthSpeed = 3.0f;
	ArmRotationSpeed = 10.0f;
}


void AMyCharacter::SetControlMode(EControlMode NewControlMode) {
	CurrentControlMode = NewControlMode;
	switch (CurrentControlMode)
	{
	case EControlMode::SHOULDERVIEW:
//		SpringArm->TargetArmLength = 450.0f;
//		SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
		ArmLengthTo = 450.0f;
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritPitch = true;
		SpringArm->bInheritRoll = true;
		SpringArm->bInheritYaw = true;
		SpringArm->bDoCollisionTest = true;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		break;

	case EControlMode::QUARTERVIEW:
//		SpringArm->TargetArmLength = 800.0f;
//		SpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
		ArmLengthTo = 800.0f;
		ArmRotationTo = FRotator(-45.0f, 0.0f, 0.0f);
		SpringArm->bUsePawnControlRotation = false;
		SpringArm->bInheritPitch = false;
		SpringArm->bInheritRoll = false;
		SpringArm->bInheritYaw = false;
		SpringArm->bDoCollisionTest = false;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		break;
	}
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, ArmLengthTo, DeltaTime, ArmLengthSpeed);

	switch(CurrentControlMode) {
	case EControlMode::QUARTERVIEW:
		SpringArm->SetRelativeRotation(FMath::RInterpTo(SpringArm->GetRelativeRotation(), ArmRotationTo, DeltaTime, ArmRotationSpeed));
		if (DirectionToMove.SizeSquared() > 0.0f) {
			GetController()->SetControlRotation(FRotationMatrix::MakeFromX(DirectionToMove).Rotator());
			AddMovementInput(DirectionToMove);
		}
		break;
	}
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Move Forward / Backward"), this, &AMyCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("Move Right / Left"), this, &AMyCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("Turn Right / Left Mouse"), this, &AMyCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("Look Up / Down Mouse"), this, &AMyCharacter::LookUp);
	PlayerInputComponent->BindAction(TEXT("View Change"), EInputEvent::IE_Pressed, this, &AMyCharacter::ViewChange);
}

void AMyCharacter::UpDown(float NewAxisValue) {
	switch (CurrentControlMode) {
	case EControlMode::SHOULDERVIEW:
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);
		break;

	case EControlMode::QUARTERVIEW:
		DirectionToMove.X = NewAxisValue;
		break;
	}
}

void AMyCharacter::LeftRight(float NewAxisValue) {
	switch (CurrentControlMode) {
	case EControlMode::SHOULDERVIEW:
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);
		break;

	case EControlMode::QUARTERVIEW:
		DirectionToMove.Y = NewAxisValue;
		break;
	}
}

void AMyCharacter::Turn(float NewAxisValue) {
	switch (CurrentControlMode) {
	case EControlMode::SHOULDERVIEW:
		AddControllerYawInput(NewAxisValue);
		break;
	}
}

void AMyCharacter::LookUp(float NewAxisValue) {
	switch (CurrentControlMode) {
	case EControlMode::SHOULDERVIEW:
		AddControllerPitchInput(NewAxisValue);
		break;
	}
}

void AMyCharacter::ViewChange() {
	switch (CurrentControlMode) {
	case EControlMode::SHOULDERVIEW:
		GetController()->SetControlRotation(GetActorRotation());
		SetControlMode(EControlMode::QUARTERVIEW);
		break;
	case EControlMode::QUARTERVIEW:
		GetController()->SetControlRotation(SpringArm->GetRelativeRotation());
		SetControlMode(EControlMode::SHOULDERVIEW);
		break;
	}
}
 