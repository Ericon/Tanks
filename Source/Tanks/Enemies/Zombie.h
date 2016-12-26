// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Zombie.generated.h"

class ATank;

UCLASS()
class TANKS_API AZombie : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AZombie();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
    
    // Set this zombie's target, The base version of this function will handle updating TergetActor and TargetAsTank
    UFUNCTION(BlueprintCallable, Category = "AI")
    void SetTarget(AActor* NewTarget);
    
    // Return the target Actor. Returning NULL indicates no target.
    UFUNCTION(BlueprintCallable, Category = "AI")
    AActor* GetTarget();
    
    // Return the target Actor as a Tank, if possible. Returning NULL indicates no target, or that the target
    UFUNCTION(BlueprintCallable, Category = "AI")
    ATank* GetTargetAsTank();
    
    UFUNCTION(BlueprintNativeEvent, Category = "AI")
    void ZombieAI(float DeltaSeconds);
    virtual void ZombieAI_Implementation(float DeltaSeconds);
    
    // This function asks the zombie if it is in position to attack ots current target. it does not actually
    UFUNCTION(BlueprintNativeEvent, Category = "AI")
    bool ZombieAIShouldAttack();
    virtual bool ZombieAIShouldAttack_Implementation();
    
    UFUNCTION(BlueprintImplementableEvent, Category = "AI")
    void ZombieWalk(float DeltaSeconds, FVector DistanceWalkedThisFrame);
    
    UFUNCTION(BlueprintImplementableEvent, Category = "AI")
    void ZombieAttack(float DeltaSeconds);
    
    UFUNCTION(BlueprintCallable, Category = "Pawn|Input", meta = (Keyworkds = "AddInput"))
    virtual void AddRotationInput(float DeltaYawDegrees);
    
    UFUNCTION(BlueprintCallable, Category = "Pawn|Input", meta = (Keyworkds = "ConsumeInput"))
    virtual float GetRotationInput();
    
    UFUNCTION(BlueprintCallable, Category = "Pawn|Input", meta = (Keyworkds = "ConsumeInput"))
    virtual float ConsumeRotationInput();
    
    UFUNCTION(BlueprintCallable, Category = "Pawn|Input", meta = (Keyworkds = "AddInput"))
    virtual void AddAttackInput();
    
    UFUNCTION(BlueprintCallable, Category = "Pawn|Input", meta = (Keyworkds = "ConsumeInput"))
    virtual bool GetAttackInput();
    
    UFUNCTION(BlueprintCallable, Category = "Pawn|Input", meta = (Keyworkds = "ConsumeInput"))
    virtual bool ConsumeAttackInput();
    
private:
    UPROPERTY(VisibleInstanceOnly, Category="AI")
    AActor* TargetActor;
    
    UPROPERTY(VisibleInstanceOnly, Category="AI")
    ATank* TargetTank;
protected:
	UPROPERTY(EditAnywhere)
    TSubclassOf<UCameraShake> HitShake;
    
    /** Current health value. Might be fun to have different values for different attack types */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zombie", meta = (ClampMin = "0.0"))
    float Health;
    
    /** Sight distance (when no target is pressent) */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zombie", meta = (ClampMin = "0.0"))
    float SightDistance;
    
    /** Sight hanlf-angle in degrees (when no target is pressent) */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zombie", meta = (ClampMin = "0.0"))
    float SightAngle;
    
    /** Max yaw speed per second in degrees. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zombie", meta = (ClampMin = "0.0"))
    float YawSpeed;
    
    /** Speed when wanderig around, or when facing away from target. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zombie", meta = (ClampMin = "0.0"))
    float WalkSpeed;
    
    /** Speed when rushing toward target. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zombie", meta = (ClampMin = "0.0"))
    float RunSpeed;
    
    /** Attack distance. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zombie", meta = (ClampMin = "0.0"))
    float AttackDistance;
    
    /** Half-angle (in degrees) for our attack. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zombie", meta = (ClampMin = "0.0"))
    float AttackAngle;
    
    /** Minimum time between attacks. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zombie", meta = (ClampMin = "0.0"))
    float AttackCooldown;
    
    /** Game Time. in seconds, when the Zombie will be allowed to attack again. */
    UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = "Zombie")
    float AttackAvailableTime;

private:
    float YawInput;
    
    uint32 bAttackInput : 1;
};
