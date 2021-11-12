// Copyright Epic Games, Inc. All Rights Reserved.

#include "Kismet/GameplayStatics.h"
#include "proj_03GameModeBase.h"

void Aproj_03GameModeBase::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);

	// Display a debug message for five seconds. 
	// The -1 "Key" value argument prevents the message from being updated or refreshed.

	
	hudManager = Cast<AManagerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	
	//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hud Ready!"));

	//hudManager->removeWidget("Mission");
}