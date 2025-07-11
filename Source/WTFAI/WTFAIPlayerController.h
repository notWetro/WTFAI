// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "LevelSelectWidget.h"
#include "WTFAIPlayerController.generated.h"

/** Forward declaration to improve compiling times */
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

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetDestinationClickAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetDestinationTouchAction;

	/** Toggle the pause menu */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PauseAction;

	UFUNCTION(BlueprintCallable)
	void ShowLevelSelect();

	// Show the Death Screen UI
	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowDeathScreen();



protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay() override;

	/** Input handlers for SetDestination action. */
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	void OnTouchTriggered();
	void OnTouchReleased();

	UFUNCTION()
	void TogglePauseMenu();





private:
	FVector CachedDestination;

	bool bIsTouch; // Is it a touch device
	float FollowTime; // For how long it has been pressed

	/** The Pause Menu widget class (found in the constructor) */
	UPROPERTY()
	TSubclassOf<UUserWidget> PauseMenuWidgetClass;

	/** The runtime instance of the Pause Menu */
	UPROPERTY()
	UUserWidget* PauseMenuInstance;

	// Class for your Level-Select UMG widget
	UPROPERTY()
	TSubclassOf<ULevelSelectWidget> LevelSelectWidgetClass;

	// Runtime instance
	UPROPERTY()
	ULevelSelectWidget* LevelSelectInstance;


	// Death Screen widget class (found in constructor) 
	UPROPERTY()
	TSubclassOf<UUserWidget> DeathScreenWidgetClass;

	// Runtime instance of the Death Screen
	UPROPERTY()
	UUserWidget* DeathScreenInstance;

};


