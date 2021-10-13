// Copyright Epic Games, Inc. All Rights Reserved.


#include "Project3GameModeBase.h"

<<<<<<< HEAD



void AFPSProjectGameModeBase::StartPlay()
{
Super::StartPlay();

check(GEngine != nullptr);

  // Display a debug message for five seconds.
  // The -1 "Key" value argument prevents the message from being updated or refreshed.
  GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is FPSGameMode!"));

}
=======
void AProject3GameModeBase::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);

	// Display a debug message for five seconds. 
	// The -1 "Key" value argument prevents the message from being updated or refreshed.
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Project3GameMode!"));

}
>>>>>>> 47a5a856779016a8f5d6d64b66e6c4d97b7e067c
