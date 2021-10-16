// Fill out your copyright notice in the Description page of Project Settings.


#include "Robot.h"

ARobot::ARobot() {

	PrimaryActorTick.bCanEverTick = true;



	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	//CameraBoom->TargetArmLength = 600.0f;


	FollowCamera = CreateAbstractDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));

	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);




}