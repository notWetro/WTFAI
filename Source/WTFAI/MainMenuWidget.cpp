#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

bool UMainMenuWidget::Initialize()
{
    bool Success = Super::Initialize();
    if (!Success) return false;

    if (!ensure(PlayButton != nullptr)) return false;
    PlayButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnPlayClicked);

    if (!ensure(QuitButton != nullptr)) return false;
    QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnQuitClicked);

    return true;
}

void UMainMenuWidget::OnPlayClicked()
{
    UGameplayStatics::OpenLevel(this, FName("Level_01"));
}

void UMainMenuWidget::OnQuitClicked()
{
    UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}
