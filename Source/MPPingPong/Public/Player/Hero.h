// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerState/PS_Hero.h"
#include "Hero.generated.h"

class UStaticMeshComponent;
class UMaterialInterface;

UCLASS()
class MPPINGPONG_API AHero : public APawn
{
    GENERATED_BODY()


    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
    AHero();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UStaticMeshComponent> HeroMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Materials")
    TObjectPtr<UMaterialInterface> BlueMaterial;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Materials")
    TObjectPtr<UMaterialInterface> RedMaterial;

    void MoveRight(float Value);

public:
    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;


    UPROPERTY(ReplicatedUsing = OnRep_Team, BlueprintReadOnly, Category = "Team")
    ETeam Team = ETeam::None;

    UFUNCTION()
    void OnRep_Team();
    void Init(ETeam Team);
};