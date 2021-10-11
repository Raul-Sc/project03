// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"

AMyPawn::AMyPawn()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Set this pawn to be controlled by the lowest-numbered player
    AutoPossessPlayer = EAutoReceiveInput::Player0;

    // Create a dummy root component we can attach things to.
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
   
    OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
   
    OurVisibleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);


    // Handle movement based on our "MoveX" and "MoveY" axes
    {
        if (!CurrentVelocity.IsZero())
        {
            FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
            SetActorLocation(NewLocation);
        }
    }
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(class UInputComponent* AInputComponent)
{
    Super::SetupPlayerInputComponent(AInputComponent);


    // Respond every frame to the values of our two movement axes, "MoveX" and "MoveY".
    AInputComponent->BindAxis("MoveX", this, &AMyPawn::Move_Foward);
    AInputComponent->BindAxis("MoveY", this, &AMyPawn::Move_Right);
}

void AMyPawn::Move_Foward(float AxisValue)
{
    // Move at 100 units per second forward or backward
    CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void AMyPawn::Move_Right(float AxisValue)
{
    // Move at 100 units per second right or left
    CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}
