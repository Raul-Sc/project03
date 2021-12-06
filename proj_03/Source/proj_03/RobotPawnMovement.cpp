// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotPawnMovement.h"
#include "DrawDebugHelpers.h"
void URobotPawnMovement::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // Make sure that everything is still valid, and that we are allowed to move.
    if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
    {
        return;
    }

    // Get (and then clear) the movement vector that we set in ACollidingPawn::Tick
    FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * 1000.0f;
 
    if (!DesiredMovementThisFrame.IsNearlyZero())
    {
        FHitResult Hit;
        SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

        // If we bumped into something, try to slide along it
        if (Hit.IsValidBlockingHit())
        {
           
            SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
        }
        else{
            //We check for gravity and add if needed
         
            addGravity();
     
        }
    }
}
void URobotPawnMovement::addGravity(){
   
    FVector start = PawnOwner->GetActorLocation();
    FVector end = start + FVector(0, 0, -45);

    FCollisionQueryParams collisionParams;
    collisionParams.AddIgnoredActor(PawnOwner);
    collisionParams.bFindInitialOverlaps = true;
    collisionParams.bTraceComplex = false;
   
   // DrawDebugLine(GetWorld(), start, end, FColor::Yellow, true, (-1, 0, 1));
    FHitResult outHit;
    bool isHit = GetWorld()->LineTraceSingleByChannel(outHit, start, end, ECC_Visibility, collisionParams);
    if (!isHit) {
      //  GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Gravity"));
        AddInputVector(FVector(0, 0, -1));
    }
    

}