// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "LevelSelectWidget.h"
#include "WTFAIPlayerController.generated.h"

class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class AWTFAIPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AWTFAIPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetDestinationClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetDestinationTouchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PauseAction;

	UFUNCTION(BlueprintCallable)
	void ShowLevelSelect();

	// Show the Death Screen UI
	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowDeathScreen();



protected:
	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay() override;

	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	void OnTouchTriggered();
	void OnTouchReleased();

	UFUNCTION()
	void TogglePauseMenu();





private:
	FVector CachedDestination;

	bool bIsTouch;
	float FollowTime;

	UPROPERTY()
	TSubclassOf<UUserWidget> PauseMenuWidgetClass;

	UPROPERTY()
	UUserWidget* PauseMenuInstance;

	// Class for your Level-Select UMG widget
	UPROPERTY()
	TSubclassOf<ULevelSelectWidget> LevelSelectWidgetClass;

	UPROPERTY()
	ULevelSelectWidget* LevelSelectInstance;

	// Death Screen widget class
	UPROPERTY()
	TSubclassOf<UUserWidget> DeathScreenWidgetClass;

	// Runtime instance of the Death Screen
	UPROPERTY()
	UUserWidget* DeathScreenInstance;

};
