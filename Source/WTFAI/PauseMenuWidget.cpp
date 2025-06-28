#include "PauseMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "WTFAIPlayerController.h"

void UPauseMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (ResumeButton)
    {
        ResumeButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnResumeClicked);
    }

    if (QuitToMenuButton)
    {
        QuitToMenuButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnQuitToMenuClicked);
    }
}

void UPauseMenuWidget::OnResumeClicked()
{
    // 1) Unpause the world
    UGameplayStatics::SetGamePaused(this, false);

    // 2) Get our player controller
    if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
    {
        // 3) Restore Enhanced Input mapping context
        if (auto MyPC = Cast<AWTFAIPlayerController>(PC))
        {
            if (ULocalPlayer* LP = Cast<ULocalPlayer>(MyPC->GetLocalPlayer()))
            {
                if (auto Sub = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
                {
                    Sub->AddMappingContext(MyPC->DefaultMappingContext, 0);
                }
            }
        }

        // 4) Show the cursor again
        PC->bShowMouseCursor = true;

        // 5) Switch back to GameAndUI input (so you can both move and click)
        FInputModeGameAndUI InputMode;
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
        InputMode.SetHideCursorDuringCapture(false);
        PC->SetInputMode(InputMode);
    }

    // 6) Finally remove the pause‐menu widget
    RemoveFromParent();
}
void UPauseMenuWidget::OnQuitToMenuClicked()
{
    UGameplayStatics::SetGamePaused(this, false);
    UGameplayStatics::OpenLevel(this, TEXT("MainMenuMap"));
}
