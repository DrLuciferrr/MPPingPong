
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PC_Hero.generated.h"

UCLASS()
class MPPINGPONG_API APC_Hero : public APlayerController
{
    GENERATED_BODY()

public:
    APC_Hero();

    virtual void SetupInputComponent() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    float MovementSpeed = 600.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    float MinBoundary = -250.5f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    float MaxBoundary = 1050;

    void MoveRight(float Value);

    UFUNCTION(Server, Unreliable)
    void ServerMoveRight(FVector ClientLocation);
};
