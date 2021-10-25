// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));

	MeshComponent->SetupAttachment(RootComponent);

	 FMove = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovement"));
	
	 bCanMove = false;

}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	//setOrientation();
	
}




// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("MoveX", this, &AMyPawn::MoveX);
	InputComponent->BindAxis("MoveY",this, &AMyPawn::MoveY);
	InputComponent->BindAxis("Turn", this, &AMyPawn::AddControllerYawInput);


}
void AMyPawn::setHeight(float dir,char rot) {
	if (dir == 0) return;
	FHitResult hit = RayCast(dir,rot);
	float height = hit.Location.Z;
	FVector newloc = GetActorLocation();
	newloc.Z = height + 60;
	SetActorLocation(newloc);
}
void AMyPawn::setOrientation() {
	FHitResult front = RayCast(1, 'f');
	FHitResult back = RayCast(-1, 'f');
	FHitResult left = RayCast(-1, 'l');
	FHitResult right = RayCast(1, 'l');

	float rise = front.Location.Z - back.Location.Z;
	float run = front.Location.X - back.Location.X;
	float angle = FMath::Atan(rise / run) * 57.2957795;
	
	FQuat rot = FQuat(FRotator(angle, Controller->GetControlRotation().Yaw, Controller->GetControlRotation().Roll));
	SetActorRotation(rot, ETeleportType::None);
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Yellow, FString::Printf(TEXT("PITCH:%f"), angle));
}
FHitResult AMyPawn::RayCast(float dir,char rot)
{
	FVector start = GetActorLocation();
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	FVector end;
	if(rot == 'f')
		 end = start + (FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X) * 200 * dir);
	else 
		end = start + (FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y) * 200 * dir);
	end.Z = (start.Z - 200);
	

	
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("Start%s"), *start.ToString()));
	DrawDebugLine(GetWorld(), start, end, FColor::Yellow, false, (0, 0, 1));

	FCollisionQueryParams collisionParams;
	collisionParams.AddIgnoredActor(this);
	collisionParams.bFindInitialOverlaps = true;
	collisionParams.bTraceComplex = false;

	FHitResult outHit;
	bool isHit = GetWorld()->LineTraceSingleByChannel(outHit, start, end, ECC_Visibility, collisionParams);
	
	return outHit;
}

void AMyPawn::MoveX(float Axis)
{
	
	if (bCanMove) {
		setHeight(Axis, 'l');
		setOrientation();
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Axis);
	}
}
void AMyPawn::MoveY(float Axis)
{


	if (bCanMove) {
		setHeight(Axis, 'f');
		setOrientation();
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Axis);
	}
}
void AMyPawn::setCanMove()
{
	//bCanMove = false;
}