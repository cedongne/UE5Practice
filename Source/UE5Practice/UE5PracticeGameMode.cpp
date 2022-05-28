// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE5PracticeGameMode.h"
#include "UE5PracticeCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUE5PracticeGameMode::AUE5PracticeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
