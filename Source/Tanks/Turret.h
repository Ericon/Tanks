// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Turret.generated.h"

class ATank;

UCLASS()
class TANKS_API ATurret : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurret();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
protected:
    // Max turn ratein degrees/second for the turret.
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Turret")
    float YawSpeed;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turret")
    ATank* Tank;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Turret")
    TSubclassOf<AActor> Projectile;
private:
    // Helpful debug tool = wich way is the tank facing
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turret", meta = (AllowPrivateAccess = "true"))
    class UArrowComponent* TurretDirection;
    
    // Sprite for the tank body
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turret", meta = (AllowPrivateAccess = "true"))
    class UPaperSpriteComponent* TurretSprite;
};
