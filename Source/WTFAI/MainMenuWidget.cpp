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
}

void UMainMenuWidget::OnStartClicked()
{
    UGameplayStatics::OpenLevel(this, FName("TopDownMap"));
}

void UMainMenuWidget::OnQuitClicked()
{
    // This will quit the game (in editor it’ll just stop play)
    APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
    UKismetSystemLibrary::QuitGame(this, PC, EQuitPreference::Quit, true);
}
