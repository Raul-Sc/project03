// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyProjectGameModeBase.h"

void AMyProjectGameModeBase::StartPlay()
{
	Super::StartPlay();
	
	check(GEngine != nullptr);

	// Display a debug message for five seconds. 
	// The -1 "Key" value argument prevents the message from being updated or refreshed.
	
	SpawnStuff();




}
void AMyProjectGameModeBase::SpawnStuff() {

	FVector spawnLocation(0, 0, 100);
	FRotator spawnRotation(0, 0, 0);
	if (mainPlayer) {
		const FActorSpawnParameters spawnParams;
		player = GetWorld()->SpawnActor<ARobot>(mainPlayer, spawnLocation, spawnRotation, spawnParams);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Spawned Player"));
	}
	if (mainBoss) {
		const FActorSpawnParameters spawnParams;
		spawnLocation += FVector(500, 500, 0);
		enemy = GetWorld()->SpawnActor<AEnemy>(mainBoss, spawnLocation, spawnRotation, spawnParams);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Spawned Enemy"));
	}

}