// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/GI_MPPingPong.h"

#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Online/OnlineSessionNames.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"


UGI_MPPingPong::UGI_MPPingPong()
{
}

void UGI_MPPingPong::Init()
{
	Super::Init();

	IOnlineSubsystem* SubSystem = IOnlineSubsystem::Get();
	if (SubSystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnlineSubsystem found: %s"), *SubSystem->GetSubsystemName().ToString());

		SessionInterface = SubSystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{

			SessionInterface = SubSystem->GetSessionInterface();
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UGI_MPPingPong::OnCreateSessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UGI_MPPingPong::OnFindSessionComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UGI_MPPingPong::OnJoinSessionComplete);
			UE_LOG(LogTemp, Warning, TEXT("SessionInterface is VALID"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("SessionInterface is INVALID"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("IOnlineSubsystem::Get() returned NULL"));
	}
}
void UGI_MPPingPong::OnCreateSessionComplete(FName ServerName, bool Succeeded)
{
	if (Succeeded)
	{
		GetWorld()->ServerTravel("/Game/MPPingPongContent/DevelopmentContent/Maps/lvl_Arena?listen");
		//GetWorld()->ServerTravel("lvl_Arena?listen");
		//UGameplayStatics::OpenLevel(GetWorld(), FName("lvl_Arena"), true, TEXT("?listen"));
	}
}
void UGI_MPPingPong::OnFindSessionComplete(bool Succeeded)
{
	UE_LOG(
		LogTemp,
		Warning,
		TEXT("Find Match: Search completed. Success=%s"),
		Succeeded ? TEXT("true") : TEXT("false")
	);

	if (!Succeeded || !SessionSearch.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Find Match: Search failed or results are invalid"));
		return;
	}

	if (Succeeded)
	{
		if (!SessionSearch.IsValid())
		{
			UE_LOG(LogTemp, Error, TEXT("SessionSearch is invalid"));
			return;
		}
		const TArray<FOnlineSessionSearchResult>& SearchResults = SessionSearch->SearchResults;

		if (SearchResults.Num() == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Find Match: No sessions found"));
			return;
		}

		if (SearchResults.Num() > 0)
		{
			UE_LOG(
				LogTemp,
				Warning,
				TEXT("Find Match: Attempting to join session")
			);

			SessionInterface->JoinSession(0, FName("PingPongSession"), SearchResults[0]);
		}
	}
}

void UGI_MPPingPong::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (Result != EOnJoinSessionCompleteResult::Success)
	{
		UE_LOG(LogTemp, Error, TEXT("JoinSession failed with result: %d"), (int32)Result);
		return;
	}

	if (!SessionInterface.IsValid())
	{
		return;
	}

	FString JoinAddress;
	if (SessionInterface->GetResolvedConnectString(SessionName, JoinAddress))
	{
		if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
		{
			PC->ClientTravel(JoinAddress, ETravelType::TRAVEL_Absolute);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get connect string"));
	}
}

void UGI_MPPingPong::CreateServer()
{
	if (!SessionInterface.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("SessionInterface is invalid in CreateServer"));
		return;
	}

	FNamedOnlineSession* ExistingSession = SessionInterface->GetNamedSession(FName("PingPongSession"));
	if (ExistingSession != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Session already exists, destroying it first..."));
		SessionInterface->DestroySession(FName("PingPongSession"));
		return;
	}

	FOnlineSessionSettings SessionSettings;

	SessionSettings.bAllowJoinInProgress = true;
	SessionSettings.bIsDedicated = false;
	SessionSettings.bIsLANMatch = true;
	SessionSettings.bShouldAdvertise = true;
	SessionSettings.bUsesPresence = true;
	SessionSettings.NumPublicConnections = 2;

	SessionInterface->CreateSession(0, FName("PingPongSession"), SessionSettings);
}
void UGI_MPPingPong::JoinServer()
{
	if (!SessionInterface.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Find Match: SessionInterface is INVALID"));
		return;
	}
	
	SessionSearch = MakeShareable(new FOnlineSessionSearch());

	SessionSearch->bIsLanQuery = true;
	SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

	SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	UE_LOG(LogTemp, Warning, TEXT("Find Match: Starting LAN session search"));

	if (!SessionInterface->FindSessions(0, SessionSearch.ToSharedRef()))
	{
		UE_LOG(LogTemp, Error, TEXT("Find Match: FindSessions failed to start"));
	}
}