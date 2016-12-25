// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanks.h"
#include "Tank.h"
#include "PaperSpriteComponent.h"
#include "Turret.h"


// Sets default values
ATurret::ATurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    RootComponent = TurretDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("TurretDirection"));

    TurretSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("TurretSprite"));
    TurretSprite->AttachToComponent(TurretDirection,FAttachmentTransformRules::KeepRelativeTransform);

    YawSpeed = 180.0f;
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();

    Tank = Cast<ATank>(GetParentActor());
    check(Tank);
}

// Called every frame
void ATurret::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

  check(TurretDirection);
  if(Tank != nullptr)
  {
    if(APlayerController* PC = Cast<APlayerController>(Tank->GetController()))
    {
      FVector2D AimLocation;
      if(PC->GetMousePosition(AimLocation.X, AimLocation.Y))
      {
        FVector2D TurretLocation = FVector2D::ZeroVector;
        UGameplayStatics::ProjectWorldToScreen(PC, TurretDirection->GetComponentLocation(), TurretLocation);
        float DesiredYaw;
        if(UTankStatics::FindLookAtAngle(TurretLocation, AimLocation, DesiredYaw))
        {
          FRotator CurrentRotation = TurretDirection->GetComponentRotation();
          float DeltaYaw = UTankStatics::FindDeltaAngleDegrees(CurrentRotation.Yaw, DesiredYaw);
          float MaxDeltaYawThisFrame = YawSpeed * DeltaTime;
          if(MaxDeltaYawThisFrame > FMath::Abs(DeltaYaw))
          {
              CurrentRotation.Yaw = DesiredYaw;
          }
          else
          {
              CurrentRotation.Yaw += (MaxDeltaYawThisFrame * FMath::Sign(DeltaYaw));
          }
          TurretDirection->SetWorldRotation(CurrentRotation);
        }
      }
    }
  }
}
