#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMenuPlayerController.generated.h"

class UUserWidget;

UCLASS()
class WTFAI_API AMainMenuPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AMainMenuPlayerController();

protected:
    virtual void BeginPlay() override;

    // Assigns our widget blueprint; set automatically in C++
    UPROPERTY()
    TSubclassOf<UUserWidget> MainMenuWidgetClass;

private:
    // Holds the created widget so it doesn’t get garbage-collected
    UPROPERTY()
    UUserWidget* MainMenuWidget;
};
