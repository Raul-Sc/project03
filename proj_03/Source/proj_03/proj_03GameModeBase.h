// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once



#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ManagerHUD.h"


#include "RobotPawn.h"
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
	ARobotPawn* player;

	FVector targetLocation;

	void spawnStuff();
};
