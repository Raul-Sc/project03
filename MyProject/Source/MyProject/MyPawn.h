// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "DrawDebugHelpers.h"


#include "MyPawn.generated.h"

UCLASS()
class MYPROJECT_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();
	UPROPERTY(EditAnywhere)
		USceneComponent* MeshComponent;
	



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	UFloatingPawnMovement* FMove;

	bool bCanMove;

	void setHeight();

	FHitResult RayCast();

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveX(float Axis);
	void MoveY(float Axis);

	UFUNCTION(BlueprintCallable, Category = Movement)
		void setCanMove();
	

};
