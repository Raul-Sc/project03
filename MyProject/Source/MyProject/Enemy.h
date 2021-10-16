// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyPawn.h"
#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AEnemy : public AMyPawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;
	
};
