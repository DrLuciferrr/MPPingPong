#include "Widgets/BaseHUD.h"
#include "Widgets/UI/Score/UW_Score.h"
#include "Blueprint/UserWidget.h"

void ABaseHUD::BeginPlay()
{
    Super::BeginPlay();

    if (!IsValid(ScoreWidgetClass))
        return;

    ScoreWidget = CreateWidget<UUW_Score>(
        GetOwningPlayerController(),
        ScoreWidgetClass
    );

    if (IsValid(ScoreWidget))
    {
        ScoreWidget->AddToViewport();
    }
}

void ABaseHUD::UpdateScore(int32 BlueScore, int32 RedScore)
{
    if (!IsValid(ScoreWidget))
        return;

    UE_LOG(
        LogTemp,
        Warning,
        TEXT("[ABaseHUD] Score: Red %d, Blue %d"),
        RedScore,
        BlueScore
    );
    ScoreWidget->UpdateScore(BlueScore, RedScore);

}