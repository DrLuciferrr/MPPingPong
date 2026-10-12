// Fill out your copyright notice in the Description page of Project Settings.


#include "GS_MPPingPong.h"

#include "Widgets/BaseHUD.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"

int32 AGS_MPPingPong::GetRedScore()
{
    return RedScore;
}

int32 AGS_MPPingPong::GetBlueScore()
{
    return BlueScore;
}

void AGS_MPPingPong::AddScore(bool bBlueTeam)
{
    if (!HasAuthority())
        return;

    if (bBlueTeam)
        BlueScore++;
    else
        RedScore++;
    OnRep_Score();

    UE_LOG(
        LogTemp,
        Warning,
        TEXT("[GS] Score: Red %d, Blue %d"),
        RedScore,
        BlueScore
    );
}

void AGS_MPPingPong::GetLifetimeReplicatedProps(
    TArray<FLifetimeProperty>& OutLifetimeProps
) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AGS_MPPingPong, BlueScore);
    DOREPLIFETIME(AGS_MPPingPong, RedScore);
}

void AGS_MPPingPong::OnRep_Score()
{
    ABaseHUD* HUD = Cast<ABaseHUD>(
        UGameplayStatics::GetPlayerController(this, 0)->GetHUD()
    );

    if (IsValid(HUD))
    {
        HUD->UpdateScore(GetBlueScore(), GetRedScore());
    }
}