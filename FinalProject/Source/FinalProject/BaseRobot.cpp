// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SphereComponent.h"

#include "BaseRobot.h"

// Sets default values
ABaseRobot::ABaseRobot()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));

	MeshComponent->SetupAttachment(RootComponent);

	FMove = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovement"));
	canMove = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetupAttachment(RootComponent);
	SphereComp->SetSphereRadius(200);

	canSwitch = false;
}

// Called when the game starts or when spawned
void ABaseRobot::BeginPlay()
{
	Super::BeginPlay();
	if (SpawnerClass) {
			// Get the camera transform.
			FVector CameraLocation;
			FRotator CameraRotation;
			GetActorEyesViewPoint(CameraLocation, CameraRotation);

			// Set MuzzleOffset to spawn projectiles slightly in front of the camera.
			MuzzleOffset.Set(100.0f, 100.0f, 0.0f);

			// Transform MuzzleOffset from camera space to world space.
			FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);

			// Skew the aim to be slightly upwards.
			FRotator MuzzleRotation = CameraRotation;
			MuzzleRotation.Pitch += 10.0f;

			UWorld* World = GetWorld();
			if (World)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnParams.Instigator = GetInstigator();

				// Spawn the projectile at the muzzle.
				weapon = World->SpawnActor<AActorSpawner>(SpawnerClass, MuzzleLocation, MuzzleRotation, SpawnParams);
				weapon->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
			}
	}
	
	
}

// Called every frame
void ABaseRobot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseRobot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveX", this, &ABaseRobot::MoveX);
	PlayerInputComponent->BindAxis("MoveY", this, &ABaseRobot::MoveY);
	PlayerInputComponent->BindAxis("Turn", this, &ABaseRobot::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ABaseRobot::AddControllerPitchInput);
	//will be moved into weapons
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ABaseRobot::Fire);
	PlayerInputComponent->BindAction("Spawn", IE_Pressed, this, &ABaseRobot::SpawnActors);
	PlayerInputComponent->BindAction("Swap", IE_Pressed, this, &ABaseRobot::Swap);
}
//will be moved into weapons
void ABaseRobot::Fire()
{
	if (weapon) {
		weapon->SpawnActor();
	}
}

void ABaseRobot::SetHeight(float dir, char rot) {
	if (dir == 0) return;
	FHitResult hit = RayCast(dir, rot);
	float height = hit.Location.Z;
	FVector newloc = GetActorLocation();
	newloc.Z = height + 100;
	SetActorLocation(newloc);
}
FHitResult ABaseRobot::RayCast(float dir, char rot)
{
	FVector start = GetActorLocation();
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	FVector end;
	if (rot == 'f')
		end = start + (FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X) * 100 * dir);
	else
		end = start + (FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y) * 100 * dir);
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

void ABaseRobot::MoveX(float Axis)
{

	if (canMove) {
		SetHeight(Axis, 'l');
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Axis);
	}
}
void ABaseRobot::MoveY(float Axis)
{


	if (canMove) {
		SetHeight(Axis, 'f');
	
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Axis);
	}
}

void ABaseRobot::SpawnActors()
{
	//Find the Actor Spawner in the world, and invoke it's Spawn Actor function
	AActor* ActorSpawnerTofind = UGameplayStatics::GetActorOfClass(GetWorld(), AActorSpawner::StaticClass());

	AActorSpawner* ActorSpawnerReference = Cast<AActorSpawner>(ActorSpawnerTofind);
	if (ActorSpawnerReference)
	{
		ActorSpawnerReference->SpawnActor();
	}
}
void ABaseRobot::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (AActorSpawner* ActorCheck = Cast<AActorSpawner>(OtherActor))
	{
		GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Blue, FString::Printf(TEXT("Press E to Swap") ));
		other = ActorCheck;
		canSwitch = true;
		
	}
}
void ABaseRobot::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (AActorSpawner* ActorCheck = Cast<AActorSpawner>(OtherActor))
	{
		GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Blue, FString::Printf(TEXT("")));
		other = nullptr;
		canSwitch = false;
	}
}
void ABaseRobot::Swap() {
	if (canSwitch) {
		if (other) {
			FVector otherloc = other->GetActorLocation();
			FRotator otherRot = other->GetActorRotation();
			other->SetActorLocationAndRotation(weapon->GetActorLocation(), weapon->GetActorRotation(), false, NULL, ETeleportType::None);
			weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			weapon->SetActorLocationAndRotation(otherloc, otherRot, false, NULL, ETeleportType::None);

			weapon = other;
			weapon->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
		}
	}
}