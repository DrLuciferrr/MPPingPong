// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PS_Hero.generated.h"

UENUM(BlueprintType)
enum class ETeam : uint8
{
	None,
	Blue,
	Red
};

UCLASS()
class MPPINGPONG_API APS_Hero : public APlayerState
{
	GENERATED_BODY()

public:
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Team")
	ETeam Team = ETeam::None;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};