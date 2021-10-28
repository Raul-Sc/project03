// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotPlayer.h"


ARobotPlayer::ARobotPlayer() {

	PrimaryActorTick.bCanEverTick = true;



	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);






	//CameraBoom->TargetArmLength = 600.0f;


	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));

	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
}


