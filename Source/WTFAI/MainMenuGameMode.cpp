#include "MainMenuGameMode.h"
#include "MainMenuPlayerController.h"

AMainMenuGameMode::AMainMenuGameMode()
{
    // No pawn needed on the menu screen
    DefaultPawnClass = nullptr;

    // Use our C++ player controller that spawns the widget
    PlayerControllerClass = AMainMenuPlayerController::StaticClass();
}
