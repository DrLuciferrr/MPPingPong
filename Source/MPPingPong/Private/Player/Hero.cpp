// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Hero.h"
#include "Net/UnrealNetwork.h"


void AHero::GetLifetimeReplicatedProps(
    TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AHero, Team);
}

// Sets default values

AHero::AHero()
{
    PrimaryActorTick.bCanEverTick = true;

    bReplicates = true;
    SetReplicateMovement(true);

    HeroMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HeroMesh"));
    SetRootComponent(HeroMesh);
}


// Called when the game starts or when spawned
void AHero::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AHero::Init(ETeam NewTeam)
{
    Team = NewTeam;
    OnRep_Team();
}

void AHero::OnRep_Team()
{
    if (!IsValid(HeroMesh))
        return;

    switch (Team)
    {
    case ETeam::Blue:
        HeroMesh->SetMaterial(0, BlueMaterial);
        break;

    case ETeam::Red:
        HeroMesh->SetMaterial(0, RedMaterial);
        break;

    default:
        break;
    }
}
