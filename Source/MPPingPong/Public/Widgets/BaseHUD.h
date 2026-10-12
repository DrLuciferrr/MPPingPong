#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BaseHUD.generated.h"

class UUW_Score;

UCLASS()
class MPPINGPONG_API ABaseHUD : public AHUD
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;

    void UpdateScore(int32 BlueScore, int32 RedScore);

protected:
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUW_Score> ScoreWidgetClass;

private:
    UPROPERTY()
    TObjectPtr<UUW_Score> ScoreWidget;
};