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
	
	 bCanMove = true;

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


}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("MoveX", this, &AMyPawn::MoveX);
	InputComponent->BindAxis("MoveY",this, &AMyPawn::MoveY);
	InputComponent->BindAxis("Turn", this, &AMyPawn::AddControllerYawInput);
//	InputComponent->BindAction("RayCast", IE_Pressed, this, &AMyPawn::Ray);

}
void AMyPawn::setHeight() {
	FHitResult hit = RayCast();
	float height = hit.Location.Z;
	FVector newloc = GetActorLocation();
	newloc.Z = height + 50;
	SetActorLocation(newloc);
}
FHitResult AMyPawn::RayCast()
{
	FVector start = GetActorLocation();
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);


	FVector end = start + (FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X) * 200);
	end.Z = -20;

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("Start%s"), *start.ToString()));
	DrawDebugLine(GetWorld(), start, end, FColor::Yellow, false, (0, 0, 1));

	FCollisionQueryParams collisionParams;
	collisionParams.AddIgnoredActor(this);
	collisionParams.bFindInitialOverlaps = true;
	collisionParams.bTraceComplex = true;

	FHitResult outHit;
	bool isHit = GetWorld()->LineTraceSingleByChannel(outHit, start, end, ECC_Visibility, collisionParams);
	if (isHit) {
		FVector normal = outHit.Normal;
		GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Yellow, (TEXT("%s"), *normal.ToString()));
	}
	return outHit;
}

void AMyPawn::MoveX(float Axis)
{

	if (bCanMove) {

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Axis);
	}
}
void AMyPawn::MoveY(float Axis)
{

	if (bCanMove) {

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		setHeight();
		AddMovementInput(Direction, Axis);
	}
}
void AMyPawn::setCanMove()
{
	//bCanMove = false;
}