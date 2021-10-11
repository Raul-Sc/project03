// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Project3GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT3_API AProject3GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

		virtual void StartPlay() override;
	
};
