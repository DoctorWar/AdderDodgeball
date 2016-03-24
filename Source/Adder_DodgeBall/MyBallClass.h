// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/Actor.h"
#include "MyBallClass.generated.h"
UENUM(BlueprintType)
namespace PowerUp
{
	enum PowerUpType
	{
		none UMETA(DisplayName = "none"),
		strength UMETA(DisplayName = "strength"),
		precision UMETA(DisplayName = "precision")
	};
}
UCLASS()
class ADDER_DODGEBALL_API AMyBallClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyBallClass();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = powerUp)
		TEnumAsByte<PowerUp::PowerUpType> currentPowerup;
	UFUNCTION(BlueprintCallable, Category = "powerUP")
		void SetPowerUp(PowerUp::PowerUpType powerUp);
	UFUNCTION(BlueprintCallable, Category = "powerUP")
		void ResetStats();
	


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = powerUp)
		float Strength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = powerUp)
		float Pricision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = powerUp)
		bool deadly;

	//By AI developers below
	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
		void LaunchBall();
	UFUNCTION()
		bool GetIsDeadly();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		AActor* OwningActor;
};
