// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class MPPINGPONG_API UUW_MainMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> Canvas;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> CreateMatchButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> CreateMatchText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> FindMatchButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> FindMatchText;

protected:
	UFUNCTION()
	void OnCreateButtonClicked();

	UFUNCTION()
	void OnFindButtonClicked();
};
