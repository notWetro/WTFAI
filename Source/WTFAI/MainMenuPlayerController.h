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

    UPROPERTY()
    TSubclassOf<UUserWidget> MainMenuWidgetClass;

private:
    UPROPERTY()
    UUserWidget* MainMenuWidget;
};
