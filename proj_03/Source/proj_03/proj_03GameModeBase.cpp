// Copyright Epic Games, Inc. All Rights Reserved.


#include "proj_03GameModeBase.h"
#include "Kismet/GameplayStatics.h"
void Aproj_03GameModeBase::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);

	// Display a debug message for five seconds. 
	// The -1 "Key" value argument prevents the message from being updated or refreshed.

	//Get refrence to HUD Blueprint
	hudManager = Cast<AManagerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	
	targetLocation = FVector(68600, 62600, 1310);
	spawnLocation = FVector(-41318, -34159, 1090);
	
	spawnStuff();
}

void Aproj_03GameModeBase::spawnStuff() {
	

	FRotator spawnRotation(0, -20, 0);
	if (mainPlayer) {
		const FActorSpawnParameters spawnParams;
		player = GetWorld()->SpawnActor<ARobotPawn>(mainPlayer, spawnLocation, spawnRotation, spawnParams);

		//attach HudManager and set target location
		player->attachHudManager(hudManager);
		player->setWaypoint(targetLocation);

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Spawned Player"));
	}
	if (finishLine) {
		const FActorSpawnParameters spawnParams;
		GetWorld()->SpawnActor<AActor>(finishLine, targetLocation, spawnRotation, spawnParams);

		//attach HudManager and set target location

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Spawned Finish"));
	}
}

void Aproj_03GameModeBase::spawnBattery() {
	
	if (player) {
		FVector location = player->GetActorLocation();
		FRotator spawnRotation = player->GetActorRotation();
		if (battery) {
			const FActorSpawnParameters spawnParams;
			ABattery* temp = GetWorld()->SpawnActor<ABattery>(battery, location, spawnRotation, spawnParams);
			float charge = player->getBatteryLife();
			temp->setCharge(charge);


			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Spawned Battery"));
		}
		player->SetActorLocation(spawnLocation);
	}

}