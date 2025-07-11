#include "DeathScreenWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

void UDeathScreenWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (RestartButton)
    {
        RestartButton->OnClicked.AddDynamic(this, &UDeathScreenWidget::OnRestartClicked);
    }

    if (QuitToMenuButton)
    {
        QuitToMenuButton->OnClicked.AddDynamic(this, &UDeathScreenWidget::OnQuitToMenuClicked);
    }

}

void UDeathScreenWidget::OnRestartClicked()
{
    // Unpause the game
    if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
    {
        UGameplayStatics::SetGamePaused(this, false);

        // Reload the current level
        FName CurrentLevel = *UGameplayStatics::GetCurrentLevelName(this);
        UGameplayStatics::OpenLevel(this, CurrentLevel);
    }

}

void UDeathScreenWidget::OnQuitToMenuClicked()
{
    // Unpause and open main menu
    if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
    {
        UGameplayStatics::SetGamePaused(this, false);
        UGameplayStatics::OpenLevel(this, TEXT("MainMenuMap"));
    }
}

