#include "ScoreTrigger/ScoreTrigger.h"
#include "Components/BoxComponent.h"
#include "GameMode/GM_Default.h"

AScoreTrigger::AScoreTrigger()
{
    PrimaryActorTick.bCanEverTick = false;

    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    SetRootComponent(CollisionBox);

    CollisionBox->SetBoxExtent(FVector(50.0f, 100.0f, 100.0f));

    CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionBox->SetCollisionObjectType(ECC_WorldDynamic);
    CollisionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
    CollisionBox->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);

    CollisionBox->SetGenerateOverlapEvents(true);
}

void AScoreTrigger::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("[AScoreTrigger] BeginPlay"));

    CollisionBox->OnComponentBeginOverlap.AddDynamic(
        this,
        &AScoreTrigger::OnBoxBeginOverlap
    );
}

void AScoreTrigger::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AScoreTrigger::OnBoxBeginOverlap(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult
)
{
    UE_LOG(LogTemp, Warning, TEXT("[AScoreTrigger] OnBoxBeginOverlap triggered"));

    if (!IsValid(OtherActor))
        return;

    const bool bIsBall = OtherActor->ActorHasTag(FName("Ball"));

    UE_LOG(
        LogTemp,
        Warning,
        TEXT("[AScoreTrigger] OtherActor: %s | Ball tag: %d"),
        *OtherActor->GetName(),
        bIsBall
    );

    if (!bIsBall || !HasAuthority())
        return;

    AGM_Default* GM = GetWorld()->GetAuthGameMode<AGM_Default>();

    if (!IsValid(GM))
        return;

    GM->AddScore(Team);
}