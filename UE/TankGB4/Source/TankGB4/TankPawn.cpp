// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "TankPlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/ArrowComponent.h"

//DECLARE_LOG_CATEGORY_EXTERN(TankLog, All, All);
//DEFINE_LOG_CATEGORY(TankLog);

// Sets default values
ATankPawn::ATankPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank body"));
	RootComponent = BodyMesh;

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank turret"));
	TurretMesh->SetupAttachment(BodyMesh);

	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Cannon setup point"));
	CannonSetupPoint->AttachToComponent(TurretMesh, FAttachmentTransformRules::KeepRelativeTransform);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm"));
	SpringArm->SetupAttachment(BodyMesh);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

}

void ATankPawn::MoveForward(float AxisValue)
{
	TargetForwardAxisValue = AxisValue;
}

void ATankPawn::MoveRight(float AxisValue)
{
	TargetRightAxisValue = AxisValue;
}

void ATankPawn::RotateRight(float AxisValue)
{
	TargetRotateAxisValue = AxisValue;
}

void ATankPawn::MoveAdd(float DeltaTime)
{
	// Tank movement
	FVector currentLocation = GetActorLocation();
	FVector forwardVector = GetActorForwardVector();
	FVector rightVector = GetActorRightVector();
	FVector movePosition = currentLocation + forwardVector * MoveSpeed * TargetForwardAxisValue * DeltaTime + rightVector * MoveSpeed * TargetRightAxisValue * DeltaTime;
	SetActorLocation(movePosition, true);

	// Tank rotation
	CurrentRotateAxisValue = FMath::Lerp(CurrentRotateAxisValue, TargetRotateAxisValue, InterpolationKey);
	//UE_LOG(LogTemp, Warning, TEXT("CurrentRotateAxisValue = %f TargetRotateAxisValue= % f"), CurrentRotateAxisValue, TargetRotateAxisValue);

	float yawRotation = RotationSpeed * TargetRotateAxisValue * DeltaTime;
	FRotator currentRotation = GetActorRotation();
	yawRotation = currentRotation.Yaw + yawRotation;
	FRotator newRotation = FRotator(0, yawRotation, 0);
	SetActorRotation(newRotation);

	// Turret rotation
	if (TankController) {
		FVector mousePos = TankController->GetMousePos();
		FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), mousePos);
		FRotator currRotation = TurretMesh->GetComponentRotation();
		targetRotation.Pitch = currRotation.Pitch;
		targetRotation.Roll = currRotation.Roll;
		TurretMesh->SetWorldRotation(FMath::Lerp(currRotation, targetRotation, TurretRotationInterpolationKey));
	}

}

void ATankPawn::Fire()
{
	if (Cannon && Cannon->GetAmmo() > 0) {
		Cannon->Fire();
		GEngine->AddOnScreenDebugMessage(20, 1, FColor::Yellow, FString::Printf(TEXT("Ammo - %d"), Cannon->GetAmmo()));
	}
	else if (Cannon->GetAmmo() == 0) {
		GEngine->AddOnScreenDebugMessage(2, 1, FColor::Red, "No ammo!");
	}
}

void ATankPawn::FireSpecial()
{
	if (Cannon && Cannon->GetAmmo() > 0) {
		Cannon->FireSpecial();
		GEngine->AddOnScreenDebugMessage(2, 1, FColor::Yellow, FString::Printf(TEXT("Ammo - %d"), Cannon->GetAmmo()));
	}
	else if (Cannon->GetAmmo() == 0) {
		GEngine->AddOnScreenDebugMessage(2, 1, FColor::Red, "No ammo!");
	}
}

void ATankPawn::ChangeCannon()
{
	if (Cannon->GetClass() == CannonClass) {
		SetupCannon(CannonClassAnother);
	}
	else {
		SetupCannon(CannonClass);
	}
}

//void ATankPawn::SetCannonClass(TSubclassOf<ACannon> CannonClass_)
//{
//	if (Cannon->GetClass() == CannonClass) {
//		CannonClass = CannonClass_;
//		
//	}
//	else {
//		CannonClassAnother = CannonClass_;
//	}
//}

void ATankPawn::SetupCannon(TSubclassOf<ACannon> CannonClassGet)
{
	if (Cannon) {
		Cannon->Destroy();
	}
	FActorSpawnParameters params;
	params.Instigator = this;
	params.Owner = this;
	Cannon = GetWorld()->SpawnActor<ACannon>(CannonClassGet, params);
	Cannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

// Called when the game starts or when spawned
void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	TankController = Cast<ATankPlayerController>(GetController());
	SetupCannon(CannonClass);
}

// Called every frame
void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveAdd(DeltaTime);

}

// Called to bind functionality to input
void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

