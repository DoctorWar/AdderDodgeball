// Fill out your copyright notice in the Description page of Project Settings.

#include "Adder_DodgeBall.h"
#include "PowerUpPickUp.h"


// Sets default values
APowerUpPickUp::APowerUpPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collider = CreateDefaultSubobject<USphereComponent>(
		TEXT("Collider"));
	Collider->SetSphereRadius(55.f);
	RootComponent = Collider;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(
		TEXT("Mesh"));
	Mesh->AttachTo(RootComponent);

	OnActorBeginOverlap.AddDynamic(this, &APowerUpPickUp::OnBeginOverlap);
}

void APowerUpPickUp::OnBeginOverlap(AActor* OtherActor)
{
	AAdder_DodgeBallCharacter* character = Cast<AAdder_DodgeBallCharacter>(OtherActor);
	if (character != NULL && character-> isAlive)
	{
		character->currentPowerup = currentPowerup;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This is an on screen message!"));
		Destroy();
	}
}
// Called when the game starts or when spawned
void APowerUpPickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APowerUpPickUp::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

