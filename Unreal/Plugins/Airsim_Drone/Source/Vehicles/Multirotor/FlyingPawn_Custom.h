// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Vehicles/Multirotor/FlyingPawn.h"
#include "FlyingPawn_Custom.generated.h"

/**
 * 
 */
UCLASS()
class AIRSIM_DRONE_API AFlyingPawn_Custom : public AFlyingPawn
{
	GENERATED_BODY()

public:

	AFlyingPawn_Custom();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
};
