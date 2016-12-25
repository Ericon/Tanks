// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//This structu cover all possible tank input schemes.
// What the inputs do can vary by tank, but the same inputs will always exist.
USTRUCT()
struct FTankInput
{
    GENERATED_BODY()
public:
    // Sanited movement input, ready to be used by game logic.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank Input")
    FVector2D MovementInput;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank Input")
    uint32 bFire1 : 1;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank Input")
    uint32 bFire2 : 1;
    
    void Sanitize();
    void MoveX(float AxisValue);
    void MoveY(float AxisValue);
    void Fire1(bool bPressed);
    void Fire2(bool bPressed);
    
private:
    FVector2D RawMovementInput;
};

UCLASS()
class TANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
private:
    void MoveX(float AxisValue);
    void MoveY(float AxisValue);
    void Fire1Pressed();
    void Fire1Released();
    void Fire2Pressed();
    void Fire2Released();
private:
    // Helpful debug tool = wich way is the tank facing
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank", meta = (AllowPrivateAccess = "true"))
    class UArrowComponent* TankDirection;
    
    // Sprite for the tank body
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank", meta = (AllowPrivateAccess = "true"))
    class UPaperSpriteComponent* TankSprite;
    
    //The Actor used as teh turret.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank", meta = (AllowPrivateAccess = "true"))
    UChildActorComponent* ChildTurret;
    
    // Our in-game camera.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank", meta = (AllowPrivateAccess = "true"))
    UCameraComponent* CameraComponent;
protected:
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank Input")
    FTankInput TankInput;
    
    //Maximum turn rate (degrees/second) of the tank
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tank", meta = (CampMin = "0.0"))
    float YawSpeed;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tank", meta = (CampMin = "0.0"))
    float MoveSpeed;
};
