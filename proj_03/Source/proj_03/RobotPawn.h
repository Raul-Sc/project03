// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "UObject/ConstructorHelpers.h"

#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
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
	UPROPERTY(EditAnywhere)
		USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
		FVector waypoint;


		float batteryLife;

	UPROPERTY(BlueprintReadOnly)
			int batteriesUsed;

	int counter; 

	bool coordsOn;
	bool coordsDrain = true;

	bool moveDrain = true;

	UPROPERTY(BlueprintReadWrite)
		bool flashLightOn;

	bool flashlightDrain = true;

	FTimerHandle coordsDrainHandle;
	FTimerHandle flashLightDrainHandle;
	FTimerHandle moveDrainHandle;

	bool statusOn = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UPawnMovementComponent* GetMovementComponent() const override;

	void attachHudManager(AManagerHUD* m);
	void setWaypoint(FVector location);

	UFUNCTION(BlueprintCallable)
	FVector getWayPoint(){ return waypoint; }

	UFUNCTION(BlueprintCallable)
		void drainBattery(float drain); 
	UFUNCTION(BlueprintCallable)
		float getBatteryLife() { return batteryLife; }

	

	void resetCoordsDrain();
	void resetLightDrain();
	void resetMoveDrain();

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void Turn(float AxisValue);
	void toggleCompass();

	UFUNCTION(BlueprintCallable)
		void toggleLight();
	UFUNCTION(BlueprintCallable)
		void toggleStatus();
};
