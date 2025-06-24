#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MenuPlayerController.generated.h"

UCLASS()
class DEINPROJECTNAME_API AMenuPlayerController : public APlayerController
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
    TSubclassOf<class UMainMenuWidget> MainMenuClass;

    UPROPERTY()
    class UMainMenuWidget* MainMenu;
};
