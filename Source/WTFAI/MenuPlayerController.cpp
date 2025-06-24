#include "MenuPlayerController.h"
#include "MainMenuWidget.h"

void AMenuPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (MainMenuClass)
    {
        MainMenu = CreateWidget<UMainMenuWidget>(this, MainMenuClass);
        if (MainMenu)
        {
            MainMenu->AddToViewport();
            bShowMouseCursor = true;
            SetInputMode(FInputModeUIOnly());
        }
    }
}
