#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerState/PS_Hero.h"
#include "ScoreTrigger.generated.h"

class UBoxComponent;

UCLASS()
class MPPINGPONG_API AScoreTrigger : public AActor
{
    GENERATED_BODY()

public:
    AScoreTrigger();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UBoxComponent> CollisionBox;

    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Team")
    ETeam Team = ETeam::None;

    UFUNCTION()
    void OnBoxBeginOverlap(
        UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );

public:
    virtual void Tick(float DeltaTime) override;
};