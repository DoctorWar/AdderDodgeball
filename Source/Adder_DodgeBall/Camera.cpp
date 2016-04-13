// Fill out your copyright notice in the Description page of Project Settings.

#include "Adder_DodgeBall.h"
#include "Camera.h"
#include "Engine.h"

// Sets default values
ACamera::ACamera()
{
	HitSomeone = false;
	Timer = 0;
	TimeStep = 50;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bTickEvenWhenPaused = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachTo(RootComponent);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(Mesh);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 1300.f;
	CameraBoom->RelativeRotation = FRotator(-90.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

										  // Create a camera...
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	Camera->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	CameraZoom = CameraBoom->TargetArmLength;
}

// Called when the game starts or when spawned
void ACamera::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	DefaultPoint = this->GetActorLocation();
	//UE_LOG(LogTemp, Error, TEXT("TimeTimeTime %d, %d, %d"),DefaultPoint.X,DefaultPoint.Y,DefaultPoint.Z);
	OurPlayerController->SetViewTarget(this);
}

// Called every frame
void ACamera::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (HitSomeone)
	{
		//UE_LOG(LogTemp, Error, TEXT("TimeTimeTime"));
		Timer = Timer - DeltaTime;
		if (Timer < 0) 
		{
			//UE_LOG(LogTemp, Error, TEXT("CAMERA IS FOUND"));
			if (CameraZooming)
			{
				
				Dis++;
				//this->SetActorLocation ( FMath::Lerp(DefaultPoint, TargetPoint, 50));

				//FVector temp = FMath::Lerp(DefaultPoint, TargetPoint, 1300 - CameraZoom / 1200);
				UE_LOG(LogTemp, Error, TEXT("X: %f"),((1300-CameraZoom)/900) );
				GoingIn();
			}
			else
			{
				GoingOut();
				//this->SetActorLocation(FMath::Lerp(TargetPoint, DefaultPoint, 0));
			}
			//GetWorld()->GetWorldSettings->TimeDilation = 1;
			//GetWorld()->GetWorldSettings->TimeDilation = 0.1;
			//if(GWorld)
			//GWorld->GetWorldSettings()->TimeDilation = 0.000000000000000001f;
			//this->CustomTimeDilation = 10;
			this->SetActorLocation(FMath::Lerp(DefaultPoint, TargetPoint, ((1300 - CameraZoom) / 900)));
			Timer = Timer + TimeStep;
		}
	}
}

void ACamera::ZoomIn(FVector Destination)
{
	TargetPoint = Destination;
	CameraZooming = true;
	//UGameplayStatics::SetGamePaused(GetWorld(), true);
	//SetActorTickEnabled(true);
	HitSomeone = true;
}

void ACamera::GoingIn()
{
	CameraZoom = CameraZoom - 10.0;

	if (CameraZoom <= 400)
	{
		CameraBoom->TargetArmLength = 400;
		CameraZoom = 400;
		CameraZooming = false;
	}
	else
	{
		CameraBoom->TargetArmLength = CameraZoom;
	}
}

void ACamera::GoingOut()
{
	CameraZoom = CameraZoom + 10.0;

	if (CameraZoom >= 1300)
	{
		CameraBoom->TargetArmLength = 1300;
		CameraZoom = 1300;
		HitSomeone = false;
	}
	else
	{
		CameraBoom->TargetArmLength = CameraZoom;
	}
}



