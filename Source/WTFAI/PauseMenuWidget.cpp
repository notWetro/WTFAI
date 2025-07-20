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
    UGameplayStatics::SetGamePaused(this, false);

    if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
    {
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

        PC->bShowMouseCursor = true;

        FInputModeGameAndUI InputMode;
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
        InputMode.SetHideCursorDuringCapture(false);
        PC->SetInputMode(InputMode);
    }

    RemoveFromParent();
}
void UPauseMenuWidget::OnQuitToMenuClicked()
{
    UGameplayStatics::SetGamePaused(this, false);
    UGameplayStatics::OpenLevel(this, TEXT("MainMenuMap"));
}
