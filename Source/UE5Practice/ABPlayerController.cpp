// Fill out your copyright notice in the Description page of Project Settings.


#include "ABPlayerController.h"

void AABPlayerController::PostInitializeComponents() {
	Super::PostInitializeComponents();
	UE5LOG_S(Warning);
}

void AABPlayerController::OnPossess(APawn* aPawn) {
	UE5LOG_S(Warning);
	Super::OnPossess(aPawn);
}

void AABPlayerController::BeginPlay() {
	Super::BeginPlay();

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
}