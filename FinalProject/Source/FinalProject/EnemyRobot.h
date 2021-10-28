// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseRobot.h"
#include "EnemyRobot.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API AEnemyRobot : public ABaseRobot
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaTime) override;
};
