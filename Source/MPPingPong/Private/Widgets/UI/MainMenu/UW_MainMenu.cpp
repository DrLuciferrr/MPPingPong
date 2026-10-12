// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/UI/MainMenu/UW_MainMenu.h"

#include "GameInstance/GI_MPPingPong.h"

#include "Components/CanvasPanel.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UUW_MainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (CreateMatchButton)
	{
		CreateMatchButton->OnClicked.AddDynamic(this, &UUW_MainMenu::OnCreateButtonClicked);
	}
	if (CreateMatchText)
	{
		CreateMatchText->SetText(FText::FromString(TEXT("Create Match")));
	}

	if (FindMatchButton)
	{
		FindMatchButton->OnClicked.AddDynamic(this, &UUW_MainMenu::OnFindButtonClicked);
	}
	if (FindMatchText)
	{
		FindMatchText->SetText(FText::FromString(TEXT("Find Match")));
	}
}

void UUW_MainMenu::OnCreateButtonClicked()
{
	if(UGI_MPPingPong* GI = GetGameInstance<UGI_MPPingPong>())
	{
		GI->CreateServer();
	}
}

void UUW_MainMenu::OnFindButtonClicked()
{
	if (UGI_MPPingPong* GI = GetGameInstance<UGI_MPPingPong>())
	{
		GI->JoinServer();
	}
}
