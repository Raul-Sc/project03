// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseRobot.h"


#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "RobotPlayer.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API ARobotPlayer : public ABaseRobot
{
	GENERATED_BODY()

public:
	ARobotPlayer();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent* FollowCamera;


	
};
