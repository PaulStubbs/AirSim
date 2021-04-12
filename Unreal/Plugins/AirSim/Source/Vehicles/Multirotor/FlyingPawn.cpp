#include "FlyingPawn.h"
#include "AirBlueprintLib.h"
#include "common/Common.hpp"

AFlyingPawn::AFlyingPawn()
{
    init_id_ = pawn_events_.getActuatorSignal().connect_member(this, &AFlyingPawn::initializeRotors);
    pawn_events_.getActuatorSignal().connect_member(this, &AFlyingPawn::setRotorSpeed);
}

void AFlyingPawn::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    
    pawn_events_.getPawnTickSignal().emit(DeltaSeconds);
}

void AFlyingPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    pawn_events_.getActuatorSignal().disconnect_all();
    
    Super::EndPlay(EndPlayReason);
}

void AFlyingPawn::NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, 
    FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
    pawn_events_.getCollisionSignal().emit(MyComp, Other, OtherComp, bSelfMoved, HitLocation,
        HitNormal, NormalImpulse, Hit);
}

void AFlyingPawn::initializeForBeginPlay()
{
}

void AFlyingPawn::setRotorSpeed(const std::vector<MultirotorPawnEvents::RotorActuatorInfo>& rotor_infos)
{
}

common_utils::UniqueValueMap<std::string, APIPCamera*> AFlyingPawn::getCameras() const
{
    common_utils::UniqueValueMap<std::string, APIPCamera*> cameras;
    return cameras;
}

void AFlyingPawn::initializeRotors(const std::vector<MultirotorPawnEvents::RotorActuatorInfo>& rotor_infos)
{
    pawn_events_.getActuatorSignal().disconnect(init_id_);
}
