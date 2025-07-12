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

    if (OptionsButton)
    {
        OptionsButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnOptionsClicked);
    }

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

void UMainMenuWidget::OnOptionsClicked()
{
   if (MenuSwitcher)
      MenuSwitcher->SetActiveWidgetIndex(2);
}
