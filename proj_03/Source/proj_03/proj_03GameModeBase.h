// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once



#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ManagerHUD.h"


#include "RobotPawn.h"
#include "Battery.h"
#include "proj_03GameModeBase.generated.h"

UCLASS()
class PROJ_03_API Aproj_03GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	virtual void StartPlay() override;
private:

	UPROPERTY()
		AManagerHUD* hudManager;
	UPROPERTY(EditAnywhere, category = ThingsToSpawn)
		TSubclassOf<class ARobotPawn> mainPlayer;

	UPROPERTY(EditAnywhere, category = ThingsToSpawn)
		TSubclassOf<class ABattery> battery;

	UPROPERTY(EditAnywhere, category = ThingsToSpawn)
		TSubclassOf<class AActor> finishLine;



	ARobotPawn* player;

	FVector targetLocation;
	FVector spawnLocation;

	void spawnStuff();
public:
	UFUNCTION(BlueprintCallable)
		void spawnBattery();
};
