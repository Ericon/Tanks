// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanks.h"
#include "Missile.h"


// Sets default values
AMissile::AMissile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Speed = 200.0f;
}

// Called when the game starts or when spawned
void AMissile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMissile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

    
}

