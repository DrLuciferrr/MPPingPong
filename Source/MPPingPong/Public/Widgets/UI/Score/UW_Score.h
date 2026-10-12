#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_Score.generated.h"

class UTextBlock;

UCLASS()
class MPPINGPONG_API UUW_Score : public UUserWidget
{
    GENERATED_BODY()

public:
    void UpdateScore(int32 BlueScore, int32 RedScore);

protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> BlueScoreText;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> RedScoreText;
};