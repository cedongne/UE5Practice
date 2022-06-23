// Fill out your copyright notice in the Description page of Project Settings.


#include "ABGameMode.h"
#include "ABPawn.h"

AABGameMode::AABGameMode() {
	DefaultPawnClass = AABPawn::StaticClass();
}
