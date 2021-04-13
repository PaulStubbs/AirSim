// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicles/Multirotor/FlyingPawn_Custom.h"


AFlyingPawn_Custom::AFlyingPawn_Custom()
{
	body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	RootComponent = body;

	ConstructorHelpers::FObjectFinder<UStaticMesh> BodyMesh(TEXT("/Airsim_Drone/Models/QuadRotor1/Quadrotor1"));
	if (BodyMesh.Object)
	{
		body->SetStaticMesh(BodyMesh.Object);
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh> PropMesh(TEXT("/Airsim_Drone/Models/QuadRotor1/Propeller"));

	//Create Props and Rotating Movements
	for(int x = 0; x < 4; x++)
	{
		UStaticMeshComponent* Prop = CreateDefaultSubobject<UStaticMeshComponent>(FName("Prop" + FString::FromInt(x)));
		Prop->SetupAttachment(RootComponent, FName("Prop" + FString::FromInt(x)));

		if (PropMesh.Object)
		{
			Prop->SetStaticMesh(PropMesh.Object);
		}

		URotatingMovementComponent* RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(FName("Rotation" + FString::FromInt(x)));
		RotatingMovementComponent->SetUpdatedComponent(Prop);

		rotating_movements.Add(RotatingMovementComponent);
		props.Add(Prop);
	}

	ConstructorHelpers::FClassFinder<APIPCamera> CameraClassFinder(TEXT("/AirSim/Blueprints/BP_PIPCamera"));
	if (CameraClassFinder.Class)
	{
		//Setup Cameras
		camera_front_center = CreateDefaultSubobject<UChildActorComponent>(TEXT("Camera_Front_Center"));
		camera_front_center->SetChildActorClass(CameraClassFinder.Class);
		camera_front_center->SetupAttachment(RootComponent, "FPV Camera");
	
		camera_front_left = CreateDefaultSubobject<UChildActorComponent>(TEXT("Camera_Front_Left"));
		camera_front_left->SetChildActorClass(CameraClassFinder.Class);
		camera_front_left->SetupAttachment(RootComponent, "Front Left Camera");
	
		camera_front_right = CreateDefaultSubobject<UChildActorComponent>(TEXT("Camera_Front_Right"));
		camera_front_right->SetChildActorClass(CameraClassFinder.Class);
		camera_front_right->SetupAttachment(RootComponent, "Front Right Camera");
	
		camera_back_center = CreateDefaultSubobject<UChildActorComponent>(TEXT("Camera_Back_Center"));
		camera_back_center->SetChildActorClass(CameraClassFinder.Class);
		camera_back_center->SetupAttachment(RootComponent, "Back Camera");
	
		camera_bottom_center = CreateDefaultSubobject<UChildActorComponent>(TEXT("Camera_Bottom_Center"));
		camera_bottom_center->SetChildActorClass(CameraClassFinder.Class);
		camera_bottom_center->SetupAttachment(RootComponent, "Bottom Camera");
	}
}

void AFlyingPawn_Custom::BeginPlay()
{
	Super::BeginPlay();
}

void AFlyingPawn_Custom::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AFlyingPawn_Custom::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

common_utils::UniqueValueMap<std::string, APIPCamera*> AFlyingPawn_Custom::getCameras() const
{
	common_utils::UniqueValueMap<std::string, APIPCamera*> cameras;
	cameras.insert_or_assign("front_center", Cast<APIPCamera>(camera_front_center->GetChildActor()));
	cameras.insert_or_assign("front_right", Cast<APIPCamera>(camera_front_right->GetChildActor()));
	cameras.insert_or_assign("front_left", Cast<APIPCamera>(camera_front_left->GetChildActor()));
	cameras.insert_or_assign("bottom_center", Cast<APIPCamera>(camera_bottom_center->GetChildActor()));
	cameras.insert_or_assign("back_center", Cast<APIPCamera>(camera_back_center->GetChildActor()));

	cameras.insert_or_assign("0", Cast<APIPCamera>(camera_front_center->GetChildActor()));
	cameras.insert_or_assign("1", Cast<APIPCamera>(camera_front_right->GetChildActor()));
	cameras.insert_or_assign("2", Cast<APIPCamera>(camera_front_left->GetChildActor()));
	cameras.insert_or_assign("3", Cast<APIPCamera>(camera_bottom_center->GetChildActor()));
	cameras.insert_or_assign("4", Cast<APIPCamera>(camera_back_center->GetChildActor()));

	cameras.insert_or_assign("", Cast<APIPCamera>(camera_front_center->GetChildActor()));
	cameras.insert_or_assign("fpv", Cast<APIPCamera>(camera_front_center->GetChildActor()));

	return cameras;
}

void AFlyingPawn_Custom::setRotorSpeed(const std::vector<MultirotorPawnEvents::RotorActuatorInfo>& rotor_infos)
{
	for (int rotor_index = 0; rotor_index < rotor_infos.size(); ++rotor_index) {
		URotatingMovementComponent* comp = rotating_movements[rotor_index];
		if (comp != nullptr) {
			comp->RotationRate.Yaw = 
                rotor_infos.at(rotor_index).rotor_speed * rotor_infos.at(rotor_index).rotor_direction *
                180.0f / M_PIf * RotatorFactor;
		}
	}
}
