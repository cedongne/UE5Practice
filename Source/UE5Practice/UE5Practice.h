// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(UE5Practice, Log, All);

#define UE5LOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define UE5LOG_S(Verbosity) UE_LOG(UE5Practice, Verbosity, TEXT("%s"), *UE5LOG_CALLINFO)
#define UE5LOG(Verbosity, Format, ...) UE_LOG(UE5Practice, Verbosity, TEXT("%s %s"), *UE5LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

#define UE5CHECK(Expr, ...) { if(!(Expr)) { UE5LOG(Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__;}}