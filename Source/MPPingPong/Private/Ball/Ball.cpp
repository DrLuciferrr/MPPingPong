// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball/Ball.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

ABall::ABall()
{
    Tags.Add(FName(TEXT("Ball")));

    PrimaryActorTick.bCanEverTick = true;

    bReplicates = true;
    SetReplicateMovement(true);

    CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));

    SetRootComponent(CollisionSphere);

    CollisionSphere->SetSphereRadius(12.0f);
    CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

    CollisionSphere->SetCollisionObjectType(ECC_WorldDynamic);
    CollisionSphere->SetCollisionResponseToAllChannels(ECR_Block);

    CollisionSphere->SetGenerateOverlapEvents(true);
    CollisionSphere->SetCollisionResponseToChannel( ECC_WorldDynamic, ECR_Overlap);

    BallMesh =  CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
    BallMesh->SetupAttachment(CollisionSphere);
    BallMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABall::BeginPlay()
{
    Super::BeginPlay();
}

void ABall::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!HasAuthority() || Velocity.IsNearlyZero()) return;
    Velocity.Z = 0.0f;

    // Перемещаем сферу с проверкой столкновений
    FHitResult Hit;

    CollisionSphere->MoveComponent(FVector(Velocity.X, Velocity.Y, 0.0f) * DeltaTime, GetActorQuat(), true, &Hit);

    if (Hit.IsValidBlockingHit())
    {
        HandleBounce(Hit);
    }
}

void ABall::LaunchBall(FVector Direction)
{
    if (!HasAuthority()) return;

    Direction.Z = 0.0f;

    if (Direction.IsNearlyZero()) return;

    Velocity = Direction.GetSafeNormal() * InitialSpeed;
}

void ABall::DestroyBall()
{
    Destroy();
}

void ABall::HandleBounce(const FHitResult& Hit)
{
    FVector Normal = Hit.ImpactNormal.GetSafeNormal();
    Normal.Z = 0.0f;
    Normal = Normal.GetSafeNormal();

    const float Dot = FVector::DotProduct(Velocity, Normal);

    if (Dot < 0.0f)  Velocity -= 2.0f * Dot * Normal;

    Velocity.Z = 0.0f;

    const float NewSpeed = FMath::Min(Velocity.Size() + SpeedIncreasePerBounce, MaxSpeed);

    Velocity = Velocity.GetSafeNormal() * NewSpeed;
    Velocity.Z = 0.0f;
}