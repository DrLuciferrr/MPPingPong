// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
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

protected:
	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	virtual void Init() override;

	virtual void OnCreateSessionComplete(FName ServerName, bool Succeeded);
	virtual void OnFindSessionComplete(bool Succeeded);
	virtual void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

public:
	UFUNCTION()
	void CreateServer();
	UFUNCTION()
	void JoinServer();
};
