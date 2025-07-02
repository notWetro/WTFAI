#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (StartButton)
    {
        StartButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnStartClicked);
    }

    if (QuitButton)
    {
        QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnQuitClicked);
    }

    if (ChooseLevelButton)
    {
        ChooseLevelButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnChooseLevelClicked);
    }

    // Ensure we start on the main‐menu panel
    if (MenuSwitcher)
    {
        MenuSwitcher->SetActiveWidgetIndex(0);
    }
}

void UMainMenuWidget::OnStartClicked()
{
    UGameplayStatics::OpenLevel(this, FName("Level_1"));
}

void UMainMenuWidget::OnQuitClicked()
{
    // This will quit the game (in editor it’ll just stop play)
    APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
    UKismetSystemLibrary::QuitGame(this, PC, EQuitPreference::Quit, true);
}

void UMainMenuWidget::OnChooseLevelClicked()
{
    
    if (MenuSwitcher)
    {   
       MenuSwitcher->SetActiveWidgetIndex(1); 
    }
        
}
