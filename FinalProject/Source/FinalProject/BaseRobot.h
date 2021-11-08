// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "DrawDebugHelpers.h"

#include "Projectile.h" //will be in weapons class

#include "Kismet/GameplayStatics.h"
#include "ActorSpawner.h"



#include "BaseRobot.generated.h"

UCLASS()
class FINALPROJECT_API ABaseRobot : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseRobot();
	UPROPERTY(EditAnywhere)
		USceneComponent* MeshComponent;
	UPROPERTY(EditAnywhere)
		UFloatingPawnMovement* FMove;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		bool canMoveFoward;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		bool canMoveBack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool canMoveRight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool canMoveLeft;
	float health;
	virtual void adjustHeightLevel();
	float heightLevel;

protected:
	void SpawnActors();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetHeight(float dir, char rot);



	FHitResult RayCast(float dir, char rot,float offset);
	FHitResult RayCast(float dir, char rot);
	void checkCollision(float dir, char rot);

	void MoveX(float Axis);
	void MoveY(float Axis);

	virtual void NotifyActorBeginOverlap(AActor* OtherActor);
	virtual void NotifyActorEndOverlap(AActor* OtherActor);
	UPROPERTY(EditAnywhere)
		class USphereComponent* SphereComp;
	AActorSpawner* other;

	void Swap();

	bool canSwitch;

public:	

	UFUNCTION()
		void Fire();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//will be moved into weapons
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset;
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AProjectile> ProjectileClass;
	UPROPERTY(EditAnywhere, Category = Spawner)
		TSubclassOf<class AActorSpawner> SpawnerClass;
	AActorSpawner* weapon;

};
