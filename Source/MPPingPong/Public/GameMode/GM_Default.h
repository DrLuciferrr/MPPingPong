// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PlayerState/PS_Hero.h"
#include "GM_Default.generated.h"

/**
 * 
 */
UCLASS()
class MPPINGPONG_API AGM_Default : public AGameMode
{
	GENERATED_BODY()
	
public:
	AGM_Default();

	void AddScore(ETeam Team);

protected:
	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual APawn* SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform) override;

	virtual void StartRound();
	virtual void RestartRound();
	virtual void GameOver();

	virtual void SpawnBall();

	void DestroyBall();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawning")
	FVector BallSpawnLocation;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<class AHero> HeroClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawning")
	TSubclassOf<AActor> BallClass;

	TObjectPtr<class ABall> Ball;

	UPROPERTY(BlueprintReadOnly, Category = "Score")
	int32 BlueScore = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Score")
	int32 RedScore = 0;
};
