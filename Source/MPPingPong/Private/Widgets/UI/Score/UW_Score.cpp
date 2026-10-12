// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/UI/Score/UW_Score.h"

#include "Components/TextBlock.h"

void UUW_Score::UpdateScore(int32 BlueScore, int32 RedScore)
{
    if (IsValid(BlueScoreText))
    {
        BlueScoreText->SetText(FText::AsNumber(BlueScore));
    }

    if (IsValid(RedScoreText))
    {
        RedScoreText->SetText(FText::AsNumber(RedScore));
    }
    UE_LOG(
        LogTemp,
        Warning,
        TEXT("[UUW_Score] Score: Red %d, Blue %d"),
        RedScore,
        BlueScore
    );
}