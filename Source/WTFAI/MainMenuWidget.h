#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetSwitcher.h"
#include "MainMenuWidget.generated.h"


class UButton;

UCLASS()
class WTFAI_API UMainMenuWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    // Called after Slate widget hierarchy is constructed
    virtual void NativeConstruct() override;

    // These will hook up to UMG buttons by name
    UPROPERTY(meta = (BindWidget))
    UButton* StartButton;

    UPROPERTY(meta = (BindWidget))
    UButton* ChooseLevelButton;

    UPROPERTY(meta = (BindWidget))
    UButton* OptionsButton;

    UPROPERTY(meta = (BindWidget))
    UButton* QuitButton;

    // For swapping between main menu and level menu
    UPROPERTY(meta = (BindWidget))
    UWidgetSwitcher* MenuSwitcher;

private:
    UFUNCTION()
    void OnStartClicked();

    UFUNCTION()
    void OnQuitClicked();

    UFUNCTION()
    void OnChooseLevelClicked();
};
