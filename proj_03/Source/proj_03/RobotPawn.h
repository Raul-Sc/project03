// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "UObject/ConstructorHelpers.h"

#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ManagerHUD.h"


#include "RobotPawn.generated.h"

UCLASS()
class PROJ_03_API ARobotPawn : public APawn
{
	GENERATED_BODY()

			UPROPERTY(EditAnywhere)
		USceneComponent* MeshComponent;

public:
	// Sets default values for this pawn's properties
	ARobotPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
		class URobotPawnMovement* OurMovementComponent;

	UPROPERTY()
		AManagerHUD* hudManager;
	UPROPERTY()
		UCameraComponent* Camera;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UPawnMovementComponent* GetMovementComponent() const override;

	void attachHudManager(AManagerHUD* m);

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void Turn(float AxisValue);
};
