
#include "PlayerController/PC_Hero.h"

#include "Player/Hero.h"
#include "Components/InputComponent.h"

APC_Hero::APC_Hero()
{
}

void APC_Hero::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (!IsValid(InputComponent))
    {
        return;
    }

    InputComponent->BindAxis(
        TEXT("MoveRight"),
        this,
        &APC_Hero::MoveRight
    );
}

void APC_Hero::MoveRight(float Value)
{
    if (FMath::IsNearlyZero(Value))
    {
        return;
    }

    AHero* Hero = Cast<AHero>(GetPawn());

    if (!IsValid(Hero))
    {
        return;
    }

    FVector NewLocation = Hero->GetActorLocation();
    const FVector RightVector = Hero->GetActorRightVector();

    NewLocation += RightVector
        * Value
        * MovementSpeed
        * GetWorld()->GetDeltaSeconds();

    NewLocation.Y = FMath::Clamp(
        NewLocation.Y,
        MinBoundary,
        MaxBoundary
    );

    // Мгновенное локальное перемещение.
    Hero->SetActorLocation(NewLocation);

    // Клиент передаёт серверу рассчитанную позицию.
    if (!HasAuthority())
    {
        ServerMoveRight(NewLocation);
    }
}

void APC_Hero::ServerMoveRight_Implementation(FVector ClientLocation)
{
    AHero* Hero = Cast<AHero>(GetPawn());

    if (!IsValid(Hero))
    {
        return;
    }

    // Сервер использует полученную координату Y.
    // Координаты X и Z остаются под контролем сервера.
    FVector ServerLocation = Hero->GetActorLocation();

    ServerLocation.Y = FMath::Clamp(
        ClientLocation.Y,
        MinBoundary,
        MaxBoundary
    );

    Hero->SetActorLocation(ServerLocation);
}
