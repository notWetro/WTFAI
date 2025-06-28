// Copyright Epic Games, Inc. All Rights Reserved.

#include "WTFAIPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "WTFAICharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputCoreTypes.h"        
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h" 
#include "UObject/ConstructorHelpers.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AWTFAIPlayerController::AWTFAIPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;

	{
		static ConstructorHelpers::FClassFinder<UUserWidget> PauseBP(
			TEXT("/Game/UI/WBP_PauseMenu.WBP_PauseMenu_C")  
		);
		if (PauseBP.Succeeded())
		{
			PauseMenuWidgetClass = PauseBP.Class;
			UE_LOG(LogTemplateCharacter, Log, TEXT("✅ Found PauseMenuWidgetClass: %s"), *PauseMenuWidgetClass->GetName());
		}
		else
		{
			UE_LOG(LogTemplateCharacter, Error, TEXT("❌ Failed to find PauseMenuWidget at path: %s"),
				TEXT("/Game/UI/WBP_PauseMenu.WBP_PauseMenu_C"));  // ← same string here
		}
	}
}



void AWTFAIPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Hide the cursor once we're in-game
	bShowMouseCursor = true;

	// Switch back to Game-Only input
	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);


}

void AWTFAIPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Bind the PauseAction (from Enhanced Input)
	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (PauseAction)
		{
			EIC->BindAction(PauseAction, ETriggerEvent::Started, this, &AWTFAIPlayerController::TogglePauseMenu);
		}
		// … your other Enhanced-Input bindings …
	}

	// As a fallback, also bind the Escape key directly
	if (InputComponent)
	{
		InputComponent->BindKey(EKeys::Escape, IE_Pressed, this, &AWTFAIPlayerController::TogglePauseMenu);
	}


	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &AWTFAIPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &AWTFAIPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &AWTFAIPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &AWTFAIPlayerController::OnSetDestinationReleased);

		// Setup touch input events
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &AWTFAIPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &AWTFAIPlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &AWTFAIPlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &AWTFAIPlayerController::OnTouchReleased);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AWTFAIPlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void AWTFAIPlayerController::OnSetDestinationTriggered()
{
    /*
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
	
	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
     */
}

void AWTFAIPlayerController::OnSetDestinationReleased()
{
    /*
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
     */
}

// Triggered every frame when the input is held down
void AWTFAIPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void AWTFAIPlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}


void AWTFAIPlayerController::TogglePauseMenu()
{
	const bool bIsPaused = UGameplayStatics::IsGamePaused(this);
	UE_LOG(LogTemplateCharacter, Warning, TEXT("🚨 TogglePauseMenu() called. GamePaused=%d"), bIsPaused);

	if (bIsPaused)
	{
		// Unpause: remove widget if it exists
		if (PauseMenuInstance)
		{
			PauseMenuInstance->RemoveFromParent();
			PauseMenuInstance = nullptr;
		}
		UGameplayStatics::SetGamePaused(this, false);
		bShowMouseCursor = false;
		SetInputMode(FInputModeGameOnly());
	}
	else
	{
		// Spawn and show the menu
		if (PauseMenuWidgetClass)
		{
			PauseMenuInstance = CreateWidget<UUserWidget>(this, PauseMenuWidgetClass);
			if (PauseMenuInstance)
			{
				PauseMenuInstance->AddToViewport(100);
			}
			else
			{
				UE_LOG(LogTemplateCharacter, Error, TEXT("Failed to CreateWidget for PauseMenuInstance"));
			}
		}
		else
		{
			UE_LOG(LogTemplateCharacter, Error, TEXT("PauseMenuWidgetClass is null"));
		}

		UGameplayStatics::SetGamePaused(this, true);
		bShowMouseCursor = true;

		FInputModeUIOnly UIInput;
		UIInput.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		if (PauseMenuInstance)
		{
			UIInput.SetWidgetToFocus(PauseMenuInstance->TakeWidget());
		}
		SetInputMode(UIInput);

	}
}

