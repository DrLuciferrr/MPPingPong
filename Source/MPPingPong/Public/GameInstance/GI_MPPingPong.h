// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GI_MPPingPong.generated.h"

/**
 * 
 */
UCLASS()
class MPPINGPONG_API UGI_MPPingPong : public UGameInstance
{
	GENERATED_BODY()
	

public:
	UGI_MPPingPong();

	virtual void Init() override;
};
