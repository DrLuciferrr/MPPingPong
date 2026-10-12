#include "GameMode/GM_Default.h"

#include "Engine/World.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerStart.h"
#include <Kismet/GameplayStatics.h>

#include "Player/Hero.h"
#include "PlayerController/PC_Hero.h"

#include "GS_MPPingPong.h"

#include "Ball/Ball.h"


AGM_Default::AGM_Default()
{
    DefaultPawnClass = AHero::StaticClass();
    PlayerStateClass = APS_Hero::StaticClass();
    PlayerControllerClass = APC_Hero::StaticClass();

    bStartPlayersAsSpectators = true;
}

void AGM_Default::AddScore(ETeam Team)
{   
    AGS_MPPingPong* GS = GetGameState<AGS_MPPingPong>();
    switch (Team)
    {
    case ETeam::Blue:
        GS->AddScore(false);
        RedScore++;
        break;
    case ETeam::Red:
        GS->AddScore(true);
        BlueScore++;
        break;
    default:
        break;
    }
    UE_LOG(
        LogTemp,
        Warning,
        TEXT("[GM] Score: Red %d, Blue %d"),
        RedScore,
        BlueScore
    );

    DestroyBall();
    RestartRound();

}

void AGM_Default::BeginPlay()
{
    Super::BeginPlay();
}

void AGM_Default::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    APS_Hero* PS = NewPlayer->GetPlayerState<APS_Hero>();

    bool bBlueTaken = false;
    bool bRedTaken = false;

    for (APlayerState* ExistingState : GameState->PlayerArray)
    {
        if (IsValid(ExistingState) || ExistingState != PS)
        {
            if (const APS_Hero* ExistingPS = Cast<APS_Hero>(ExistingState))
            {
                 if (ExistingPS->Team == ETeam::Blue)
                     bBlueTaken = true;
                 else if (ExistingPS->Team == ETeam::Red)
                     bRedTaken = true;
            }
        }
    }

    // 3. Назначаем первую свободную команду
    if (!bBlueTaken)
    {
        PS->Team = ETeam::Blue;
        bBlueTaken = true;
    }
    else if (!bRedTaken)
    {
        PS->Team = ETeam::Red;
        bRedTaken = true;
    }

    // 4. Определяем тег нужной точки спавна
    const FName DesiredTag =  PS->Team == ETeam::Blue ? FName(TEXT("Blue")) : FName(TEXT("Red"));

    TArray<AActor*> Starts;

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), Starts);

    APlayerStart* SelectedStart = nullptr;

    for (AActor* Actor : Starts)
    {
        APlayerStart* Start = Cast<APlayerStart>(Actor);

        if (IsValid(Start) && Start->PlayerStartTag == DesiredTag)
        {
            SelectedStart = Start;
            break;
        }
    }

    // 5. Удаляем старого персонажа, если он существует
    if (APawn* OldPawn = NewPlayer->GetPawn())
    {
        NewPlayer->UnPossess();
        OldPawn->Destroy();
    }

    // 6. Создаём нового персонажа в нужной точке
    FActorSpawnParameters SpawnParams;

    SpawnParams.Owner = NewPlayer;
    SpawnParams.Instigator = nullptr;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    // if (!HeroClass) return;

    AHero* NewHero = GetWorld()->SpawnActor<AHero>(HeroClass, SelectedStart->GetActorTransform(), SpawnParams);
    NewHero->Init(PS->Team);

    // 7. Передаём управление персонажем контроллеру
    NewPlayer->Possess(NewHero);

    if (bBlueTaken && bRedTaken)
    {
        StartRound();
    }
}

//--------------------------------------------------
// SpawnDefaultPawnAtTransform
//--------------------------------------------------

APawn* AGM_Default::SpawnDefaultPawnAtTransform_Implementation(
    AController* NewPlayer,
    const FTransform& SpawnTransform)
{

    UClass* PawnClass = GetDefaultPawnClassForController(NewPlayer);

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    return GetWorld()->SpawnActor<APawn>(PawnClass, SpawnTransform, SpawnParams);
}

void AGM_Default::StartRound()
{
    UE_LOG(LogTemp, Error, TEXT("[INFO] RoundStart"));
    SpawnBall();
}

void AGM_Default::RestartRound()
{
    if (RedScore >= 5 || BlueScore >= 5) GameOver();
    else StartRound();
}

void AGM_Default::GameOver()
{
}

void AGM_Default::SpawnBall()
{
    Ball = GetWorld()->SpawnActor<ABall>(BallClass,BallSpawnLocation,FRotator::ZeroRotator);

    float Rand = FMath::FRandRange(-0.45f, 0.45f);
    Ball->LaunchBall(FVector(0.75f, Rand, 0.0f));
    UE_LOG(LogTemp, Warning, TEXT("[GM] Ball spawned successfully"));
}

void AGM_Default::DestroyBall()
{
    UE_LOG(LogTemp, Warning, TEXT("[GM] Ball destroyed"));
    Ball->DestroyBall();
}
