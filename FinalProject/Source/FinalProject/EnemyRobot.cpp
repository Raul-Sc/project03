// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyRobot.h"


void AEnemyRobot::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}
void AEnemyRobot::setHeight(float offset) {
	
	FHitResult front = RayCast(1,'f', 0);
	FHitResult back = RayCast(-1,'f', 0);
	FHitResult left = RayCast(-1, 'l', 0);
	FHitResult right = RayCast(1, 'l', 0);

	
	
	
	float h1 = front.Location.Z;
	float h2 = left.Location.Z;
	float h3 = right.Location.Z;
	float h4 = back.Location.Z;

	FString name = front.GetActor()->GetName();
	FString rightStr, leftStr;
	bool get = name.Split("_", &leftStr, &rightStr, ESearchCase::IgnoreCase, ESearchDir::FromStart);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("%s"), *rightStr));
	
	float height = (h1 + h2 + h3+ h4) / 4;
	FVector newloc = GetActorLocation();
	newloc.Z = height + offset;
	SetActorLocation(newloc);
}