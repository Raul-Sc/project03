// Copyright Epic Games, Inc. All Rights Reserved.

#include "Kismet/GameplayStatics.h"
#include "proj_03GameModeBase.h"

void Aproj_03GameModeBase::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);

	// Display a debug message for five seconds. 
	// The -1 "Key" value argument prevents the message from being updated or refreshed.

	//Get refrence to HUD Blueprint
	hudManager = Cast<AManagerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());

	targetLocation = FVector(0, 0, 0);
	
	spawnStuff();
	
}

void Aproj_03GameModeBase::spawnStuff() {

	FVector spawnLocation(0, 0, 50);
	FRotator spawnRotation(0, 0, 0);
	if (mainPlayer) {
		const FActorSpawnParameters spawnParams;
		player = GetWorld()->SpawnActor<ARobotPawn>(mainPlayer, spawnLocation, spawnRotation, spawnParams);

		//attach HudManager and set target location
		player->attachHudManager(hudManager);
		player->setWaypoint(targetLocation);

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Spawned Player"));
	}
}