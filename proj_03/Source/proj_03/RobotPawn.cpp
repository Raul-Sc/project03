// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotPawn.h"
#include "RobotPawnMovement.h"
#include "Misc/OutputDeviceNull.h"
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
	counter = 0;
	coordsOn = false;
	flashLightOn = false;

	batteriesUsed = 0;
}
void ARobotPawn::attachHudManager(AManagerHUD* m) {

	if (m) {
		hudManager = m;
	}
	


}
void ARobotPawn::setWaypoint(FVector location) {
	waypoint = location;
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
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Battery: %f"),batteryLife ));
	if (coordsOn) {
		if (coordsDrain) {
			coordsDrain = false;
			drainBattery(0.5);
			GetWorld()->GetTimerManager().SetTimer(coordsDrainHandle, this, &ARobotPawn::resetCoordsDrain, 1, false);
		}
	}
	if (flashLightOn) {
		if (flashlightDrain) {
			flashlightDrain = false;
			drainBattery(1.5);
			GetWorld()->GetTimerManager().SetTimer(flashLightDrainHandle, this, &ARobotPawn::resetLightDrain, 1, false);
		}
	}
	
}
void ARobotPawn::resetCoordsDrain() {
	coordsDrain = true;
	GetWorldTimerManager().ClearTimer(coordsDrainHandle);
}
void ARobotPawn::resetLightDrain() {
	flashlightDrain = true;
	GetWorldTimerManager().ClearTimer(flashLightDrainHandle);
}
void ARobotPawn::resetMoveDrain() {
	moveDrain = true;
	GetWorldTimerManager().ClearTimer(moveDrainHandle);
}
// Called to bind functionality to input
void ARobotPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ARobotPawn::MoveForward);
	//PlayerInputComponent->BindAxis("MoveRight", this, &ARobotPawn::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ARobotPawn::Turn);

	PlayerInputComponent->BindAction("ToggleCompass", EInputEvent::IE_Pressed, this, &ARobotPawn::toggleCompass);
	//Already in Blueprint 
	//PlayerInputComponent->BindAction("ToggleLight", EInputEvent::IE_Pressed, this, &ARobotPawn::toggleLight);
	
}
void ARobotPawn::toggleCompass()
{
	if (coordsOn) {
		coordsOn = false;
		hudManager->turnWidgetOff("Coordinates");
		hudManager->turnWidgetOff("Marker");
		hudManager->turnWidgetOff("Waypoint");
	}
	else {
		coordsOn = true;
		hudManager->turnWidgetOn("Coordinates");
		hudManager->turnWidgetOn("Marker");
		hudManager->turnWidgetOn("Waypoint");
	}
}
void ARobotPawn::toggleLight() {
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("Light: %d"), flashLightOn));
	if (flashLightOn) flashLightOn = false;
	else flashLightOn = true;
}
void ARobotPawn::toggleStatus() {
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("Light: %d"), flashLightOn));
	if (statusOn) {
		statusOn = false;
		hudManager->turnWidgetOff("Status");
	}
	else {
		statusOn = true;
		hudManager->turnWidgetOn("Status");
	}
}

UPawnMovementComponent* ARobotPawn::GetMovementComponent() const
{
	return OurMovementComponent;
}


void ARobotPawn::MoveForward(float AxisValue)
{
	
	if (!AxisValue) {
		resetMoveDrain();
		return;
	}
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{

		OurMovementComponent->AddInputVector(GetActorForwardVector() * AxisValue);
		if (moveDrain) {
			moveDrain = false;
			drainBattery(.7);
			GetWorld()->GetTimerManager().SetTimer(moveDrainHandle, this, &ARobotPawn::resetMoveDrain, 1, false);
		}

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

void ARobotPawn::drainBattery(float drain) {
	batteryLife -= drain;
	if (batteryLife > 100) batteryLife = 100;
	hudManager->bpSetBattery();

	if (batteryLife < 0) {
		if (coordsOn) toggleCompass();
		if (flashLightOn) toggleLight();
		if (this->FindFunction("PlayerDead")) {
			const FString command = FString::Printf(TEXT("PlayerDead"));
			FOutputDeviceNull od;
			this->CallFunctionByNameWithArguments(*command, od, NULL, true);
		}
	}
}