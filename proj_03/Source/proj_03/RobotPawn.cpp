// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotPawn.h"
#include "RobotPawnMovement.h"

// Sets default values
ARobotPawn::ARobotPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(40.0f);
	
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	//Editable Mesh 
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);

	// Use a spring arm to give the camera smooth, natural-feeling motion.
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 400.0f;
	//SpringArm->bEnableCameraLag = true;
	//SpringArm->CameraLagSpeed = 10.0f;

	//camera component
	 Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	// Create an instance of our movement component, and tell it to update the root.
	OurMovementComponent = CreateDefaultSubobject<URobotPawnMovement>(TEXT("CustomMovementComponent"));
	OurMovementComponent->UpdatedComponent = RootComponent;

	// Take control of the default player
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	batteryLife = 100;
}
void ARobotPawn::attachHudManager(AManagerHUD* m) {

	if (m) {
		hudManager = m;
	}
	//remove later ?
	hudManager->turnWidgetOn("Coordinates");
	hudManager->turnWidgetOn("Marker");

}
void ARobotPawn::setWaypoint(FVector location) {
	waypoint = location;
	hudManager->turnWidgetOn("Waypoint");
}
// Called when the game starts or when spawned
void ARobotPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARobotPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Battery: %f"),batteryLife ));
	
}

// Called to bind functionality to input
void ARobotPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ARobotPawn::MoveForward);
	//PlayerInputComponent->BindAxis("MoveRight", this, &ARobotPawn::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ARobotPawn::Turn);
}

UPawnMovementComponent* ARobotPawn::GetMovementComponent() const
{
	return OurMovementComponent;
}


void ARobotPawn::MoveForward(float AxisValue)
{
	if (!AxisValue) return;
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		OurMovementComponent->AddInputVector(GetActorForwardVector() * AxisValue);
		if(hudManager) hudManager->bpSetWaypoint();
	}
}

void ARobotPawn::MoveRight(float AxisValue)
{
	if (!AxisValue) return;
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		OurMovementComponent->AddInputVector(GetActorRightVector() * AxisValue);
		if(hudManager) hudManager->bpSetWaypoint();
	}
}

void ARobotPawn::Turn(float AxisValue)
{
	if (!AxisValue) return;
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += AxisValue;
	SetActorRotation(NewRotation);
	
	if (hudManager) {
		hudManager->bpSetDirection();
		hudManager->bpSetWaypoint();
	}
}
