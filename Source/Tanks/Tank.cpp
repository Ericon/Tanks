// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanks.h"
#include "PaperSpriteComponent.h"
#include "Tank.h"

void FTankInput::Sanitize()
{
    MovementInput = RawMovementInput.ClampAxes(-1.0f, 1.0f);
    MovementInput = MovementInput.GetSafeNormal();
    RawMovementInput.Set(0.0f, 0.0f);
}

void FTankInput::MoveX(float AxisValue)
{
    RawMovementInput.X += AxisValue;
}

void FTankInput::MoveY(float AxisValue)
{
    RawMovementInput.Y += AxisValue;
}

void FTankInput::Fire1(bool bPressed)
{
    bFire1 = bPressed;
}

void FTankInput::Fire2(bool bPressed)
{
    bFire2 = bPressed;
}

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    if(!RootComponent) {
        RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("TankBase"));
    }
    
    TankDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("TankDirection"));
    TankDirection->AttachToComponent(RootComponent,	FAttachmentTransformRules::KeepRelativeTransform);
    
    TankSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("TankSprite"));
    TankSprite->AttachToComponent(TankDirection,	 FAttachmentTransformRules::KeepRelativeTransform);
    
    ChildTurret = CreateDefaultSubobject<UChildActorComponent>(TEXT("ChildTurret"));
    ChildTurret->AttachToComponent(TankDirection, FAttachmentTransformRules::KeepRelativeTransform);
    
    USpringArmComponent* SprintArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SprintArm"));
    SprintArm->TargetArmLength = 500.0f;
    SprintArm->bEnableCameraLag = true;
    SprintArm->bEnableCameraRotationLag = false;
    SprintArm->bUsePawnControlRotation = false;
    SprintArm->CameraLagSpeed = 2.0f;
    SprintArm->bDoCollisionTest = false;
    SprintArm->AttachToComponent(RootComponent,	FAttachmentTransformRules::KeepRelativeTransform);
    SprintArm->SetWorldRotation(FRotator(-90.0f,0.0f,0.0f));
    
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    CameraComponent->bUsePawnControlRotation = false;
    CameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
    CameraComponent->OrthoWidth = 1024.0f;
    CameraComponent->AspectRatio = 3.0f / 4.0f;
    CameraComponent->AttachToComponent(SprintArm, FAttachmentTransformRules::KeepRelativeTransform, USpringArmComponent::SocketName);
    CameraComponent->SetWorldRotation(FRotator(-90.0f,0.0f,0.0f));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATank::DamageHealth(float Damage)
{
    
}

// Called every frame
void ATank::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

    TankInput.Sanitize();
    // Move the tank
    {
        FVector DesiredMovementDirection = FVector(TankInput.MovementInput.X, TankInput.MovementInput.Y, 0.0f);
        if(!DesiredMovementDirection.IsNearlyZero())
        {
            FRotator MovementAngle = DesiredMovementDirection.Rotation();
            float DeltaYaw = UTankStatics::FindDeltaAngleDegrees(TankDirection->GetComponentRotation().Yaw, MovementAngle.Yaw);
            bool bReverse = false;
            if(DeltaYaw != 0.0f)
            {
                float AdjustedDeltaYaw = DeltaYaw;
                if(AdjustedDeltaYaw < -90.0f)
                {
                    AdjustedDeltaYaw += 180.0f;
                    bReverse = true;
                }
                else if(AdjustedDeltaYaw > 90.0f)
                {
                    AdjustedDeltaYaw -= 180.0f;
                    bReverse = true;
                }

                float MaxYawThisFrame = YawSpeed * DeltaTime;
                if(MaxYawThisFrame >= FMath::Abs(AdjustedDeltaYaw))
                {
                    if(bReverse)
                    {
                        FRotator FacingAngle = MovementAngle;
                        FacingAngle.Yaw = MovementAngle.Yaw + 180.0f;
                        TankDirection->SetWorldRotation(FacingAngle);
                    }
                    else
                    {
                        TankDirection->SetWorldRotation(MovementAngle);
                    }
                }
                else
                {
                    TankDirection->AddLocalRotation(FRotator(0.0f, FMath::Sign(AdjustedDeltaYaw) * MaxYawThisFrame, 0.0f));
                }
                
            }
            
            {
                FVector MovementDirection = TankDirection->GetForwardVector() * (bReverse ? -1.0f : 1.0f);
                FVector Pos = GetActorLocation();
                Pos.X += MovementDirection.X * MoveSpeed * DeltaTime;
                Pos.Y += MovementDirection.Y * MoveSpeed * DeltaTime;
                SetActorLocation(Pos);
            }
            
        }
    }
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
    
    InputComponent->BindAxis("MoveX", this, &ATank::MoveX);
    InputComponent->BindAxis("MoveY", this, &ATank::MoveY);
    InputComponent->BindAction("Fire1", EInputEvent::IE_Pressed, this, &ATank::Fire1Pressed);
    InputComponent->BindAction("Fire1", EInputEvent::IE_Released, this, &ATank::Fire1Released);
    InputComponent->BindAction("Fire2", EInputEvent::IE_Pressed, this, &ATank::Fire2Pressed);
    InputComponent->BindAction("Fire2", EInputEvent::IE_Released, this, &ATank::Fire2Released);
}

void ATank::MoveX(float AxisValue)
{
    TankInput.MoveX(AxisValue);
}

void ATank::MoveY(float AxisValue)
{
    TankInput.MoveY(AxisValue);
}

void ATank::Fire1Pressed()
{
    TankInput.Fire1(true);
}

void ATank::Fire1Released()
{
    TankInput.Fire1(false);
}

void ATank::Fire2Pressed()
{
    TankInput.Fire2(true);
}

void ATank::Fire2Released()
{
    TankInput.Fire2(false);
}

