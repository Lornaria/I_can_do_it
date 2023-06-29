// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Engine/Engine.h"

// Sets default values
ACannon::ACannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* sceneCmp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceneCmp;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannon mesh"));
	Mesh->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn point"));
	ProjectileSpawnPoint->SetupAttachment(Mesh);

}

void ACannon::Fire()
{
	if (!ReadyToFire) {
		return;
	}
	ReadyToFire = false;

	if (Type == ECannonType::FireProjectile) {
		GEngine->AddOnScreenDebugMessage(1, 1, FColor::Green, "Fire - projectile");
		Ammo--;
		GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1 / FireRate, false);
	}
	else if (Type == ECannonType::FireTrace) {
		GEngine->AddOnScreenDebugMessage(1, 1, FColor::Green, "Fire - trace");
		GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1 / FireRate, false);
	}
	else if (Type == ECannonType::Autocannon) {
		GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle2, this, &ACannon::FireAutocannon, AutocannonReloadTime, true, 0.01);
		Ammo--;
	}
	
}

void ACannon::FireSpecial()
{
	if (!ReadyToFire) {
		return;
	}
	ReadyToFire = false;
	Ammo--;
	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Blue, "Fire special");
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1 / FireRate, false);
}

bool ACannon::IsReadyToFire()
{
	return ReadyToFire;
}

int ACannon::GetAmmo()
{
	return Ammo;
}

// Called when the game starts or when spawned
void ACannon::BeginPlay()
{
	Super::BeginPlay();
	Reload();
	
}

void ACannon::Reload()
{
	ReadyToFire = true;
}

void ACannon::FireAutocannon()
{
	if (AutocannonNumProjectilesFired == AutocannonNumProjectilesToFire) {
		GetWorld()->GetTimerManager().ClearTimer(ReloadTimerHandle2);
		AutocannonNumProjectilesFired = 0;
		GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1 / FireRate, false);
		return;
	}
	AutocannonNumProjectilesFired++;
	GEngine->AddOnScreenDebugMessage(AutocannonNumProjectilesFired + 1, 1, FColor::Purple, "Fire - autocannon projectile");
	UE_LOG(LogTemp, Warning, TEXT("AutocannonNumProjectilesFired = %d"), AutocannonNumProjectilesFired);
}

// Called every frame
void ACannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

