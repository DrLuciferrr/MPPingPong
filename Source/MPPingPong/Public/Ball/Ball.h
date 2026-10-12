// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class MPPINGPONG_API ABall : public AActor
{
    GENERATED_BODY()

public:
    ABall();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ball")
    TObjectPtr<USphereComponent> CollisionSphere;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ball")
    TObjectPtr<UStaticMeshComponent> BallMesh;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ball")
    float InitialSpeed = 1200.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ball")
    float MaxSpeed = 2500.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ball")
    float SpeedIncreasePerBounce = 30.0f;

    FVector Velocity = FVector::ZeroVector;

public:
    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "Ball")
    void LaunchBall(FVector Direction);

    UFUNCTION(BlueprintCallable, Category = "Ball")
    void DestroyBall();

private:
    void HandleBounce(const FHitResult& Hit);
};