// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DeathScreenWidget.generated.h"


class UButton;

UCLASS()
class WTFAI_API UDeathScreenWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	// Bound widgets from the UMG Designer
	UPROPERTY(meta = (BindWidget))
	UButton* RestartButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitToMenuButton;

private:
	// Handlers for button clicks
	UFUNCTION()
	void OnRestartClicked();

	UFUNCTION()
	void OnQuitToMenuClicked();

};
