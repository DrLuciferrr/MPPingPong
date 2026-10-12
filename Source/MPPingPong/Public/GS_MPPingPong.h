// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GS_MPPingPong.generated.h"

/**
 * 
 */
UCLASS()
class MPPINGPONG_API AGS_MPPingPong : public AGameState
{
    GENERATED_BODY()

protected:
    UPROPERTY(ReplicatedUsing = OnRep_Score, BlueprintReadOnly, Category = "Score")
    int32 BlueScore = 0;

    UPROPERTY(ReplicatedUsing = OnRep_Score, BlueprintReadOnly, Category = "Score")
    int32 RedScore = 0;

    UFUNCTION()
    void OnRep_Score();

public:

    int32 GetRedScore();
    int32 GetBlueScore();

    void AddScore(bool bBlueTeam);

    virtual void GetLifetimeReplicatedProps(
        TArray<FLifetimeProperty>& OutLifetimeProps
    ) const override;
};