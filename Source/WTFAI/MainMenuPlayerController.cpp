#include "MainMenuPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

AMainMenuPlayerController::AMainMenuPlayerController()
{
    static ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(
        TEXT("/Game/UI/WBP_MainMenu.WBP_MainMenu_C")
    );

    if (MenuBPClass.Succeeded())
    {
        MainMenuWidgetClass = MenuBPClass.Class;
    }
}

void AMainMenuPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (MainMenuWidgetClass)
    {
        // Create the widget
        MainMenuWidget = CreateWidget<UUserWidget>(this, MainMenuWidgetClass);
        if (MainMenuWidget)
        {
            // Add to viewport
            MainMenuWidget->AddToViewport();

            // Show mouse cursor
            bShowMouseCursor = true;

            // Lock input to UI only
            FInputModeUIOnly InputMode;
            InputMode.SetWidgetToFocus(MainMenuWidget->TakeWidget());
            SetInputMode(InputMode);
        }
    }
}
