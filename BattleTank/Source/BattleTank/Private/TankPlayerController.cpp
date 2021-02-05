// Fill out your copyright notice in the Description page of Project Settings.

//#include "BattleTank.h"
#include "TankPlayerController.h"



void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) 
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing tank "));

	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing:  %s"), *(ControlledTank->GetName()));

	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	AimTowardCrossahair();
}

ATank* ATankPlayerController::GetControlledTank() const 
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardCrossahair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; //Out parameter
	if (GetSightRayHitLocation(HitLocation))
	{
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());

	}


		//TODO Tell controlled tank to aim at this point
}

	//Get world location if linetrace through crosshair, true if it hits landscape 
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	//Find the crosshair position in pixel coordinates
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
	auto ScreenLocation = FVector2D(ViewPortSizeX * CrosshairXLocation, ViewPortSizeY * CrosshairYLocation);

	//De-project the screen projection of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *LookDirection.ToString());

	}
	

	//The screen position of the crosshair
	HitLocation = FVector(1.0);
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);

}

