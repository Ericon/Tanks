// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "ZombieBrains.generated.h"

/**
 * 
 */
class AZombie;

UCLASS()
class TANKS_API AZombieBrains : public AAIController
{
	GENERATED_BODY()
public:
    
    virtual void Tick(float DeltaTime) override;
	
    virtual void Possess(APawn* InPawn) override;
    virtual void UnPosses();
    
protected:
    UPROPERTY(BlueprintReadOnly, Category = "Zombie")
    AZombie* PawnAsZombie;
};
