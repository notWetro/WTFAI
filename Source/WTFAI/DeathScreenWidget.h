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

	// Sound to play when Death Screen appears
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio", meta = (AllowPrivateAccess = "true"))
	USoundBase* DeathMusic;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	USoundBase* DieSound = nullptr;

private:
	// Handlers for button clicks
	UFUNCTION()
	void OnRestartClicked();

	UFUNCTION()
	void OnQuitToMenuClicked();

};
