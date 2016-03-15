// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Camera.generated.h"

UCLASS()
class ADDER_DODGEBALL_API ACamera : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

public:	
	// Sets default values for this actor's properties
	ACamera();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = StaticCamera)
		void ZoomIn(FVector Destination);
protected:

	UFUNCTION(BlueprintCallable, Category = StaticCamera)
		void GoingIn();
	UFUNCTION(BlueprintCallable, Category = StaticCamera)
		void GoingOut();
	
	bool HitSomeone;

	float CameraZoom;
	
	bool CameraZooming;

	FVector DefaultPoint;
	FVector TargetPoint;

	float Dis = 0;
	//Time between zoomin/zoomout in seconds,
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		float TimeStep;
	//Counter to go with time step
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		float Timer;

};
