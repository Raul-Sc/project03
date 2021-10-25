// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Robot.h"
#include "Enemy.h"


#include "MyProjectGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AMyProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
		

private:
	UPROPERTY(EditAnywhere,category=ThingsToSpawn)
		TSubclassOf<class ARobot> mainPlayer;
	UPROPERTY(EditAnywhere, category = ThingsToSpawn)
		TSubclassOf<class AEnemy> mainBoss;
	ARobot* player;
	AEnemy* enemy;
	virtual void StartPlay() override;
	void SpawnStuff();
	
};
