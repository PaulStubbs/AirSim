#pragma once

#include "GameFramework/RotatingMovementComponent.h"

#include "PIPCamera.h"
#include "common/common_utils/UniqueValueMap.hpp"
#include "MultirotorPawnEvents.h"

#include "FlyingPawn.generated.h"

UCLASS()
class AIRSIM_API AFlyingPawn : public APawn
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debugging")
    float RotatorFactor = 1.0f;

    AFlyingPawn();
    virtual void Tick(float DeltaSeconds) override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation,
        FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

    //interface
    MultirotorPawnEvents* getPawnEvents()
    {
        return &pawn_events_;
    }

    //called by API to setup for begin play (Currently not Used)
    void initializeForBeginPlay();
    
    //called to get cameras
    virtual common_utils::UniqueValueMap<std::string, APIPCamera*> getCameras() const;
    
    //called by API to set rotor speeds
    virtual void setRotorSpeed(const std::vector<MultirotorPawnEvents::RotorActuatorInfo>& rotor_infos);

    //called by API to setup rotors (Currently not used)
    void initializeRotors(const std::vector<MultirotorPawnEvents::RotorActuatorInfo>& rotor_infos);

protected:
    MultirotorPawnEvents pawn_events_;
    int init_id_;
};
