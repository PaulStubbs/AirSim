// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "PIPCamera.h"
#include "common/common_utils/UniqueValueMap.hpp"
#include "vehicles/multirotor/MultirotorPawnEvents.h"
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
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//returns map of cameras to camera name
	virtual common_utils::UniqueValueMap<std::string, APIPCamera*> getCameras() const override;
    
	//called by API to set rotor speed
	virtual void setRotorSpeed(const std::vector<MultirotorPawnEvents::RotorActuatorInfo>& rotor_infos) override;

private:
	//Components
	//Rotating Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<URotatingMovementComponent*> rotating_movements;

	//Meshes
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* body;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<UStaticMeshComponent*> props;

	//Cameras
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* camera_front_left;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* camera_front_right;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* camera_front_center;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* camera_back_center;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* camera_bottom_center;
};
