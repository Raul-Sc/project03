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
	
	spawnStuff();
	
}

void Aproj_03GameModeBase::spawnStuff() {

	FVector spawnLocation(0, 0, 100);
	FRotator spawnRotation(0, 0, 0);
	if (mainPlayer) {
		const FActorSpawnParameters spawnParams;
		player = GetWorld()->SpawnActor<ARobotPawn>(mainPlayer, spawnLocation, spawnRotation, spawnParams);

		//attach HudManager
		player->attachHudManager(hudManager);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Spawned Player"));
	}
}