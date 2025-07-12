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
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    UButton* StartButton;

    UPROPERTY(meta = (BindWidget))
    UButton* ChooseLevelButton;

    UPROPERTY(meta = (BindWidget))
    UButton* OptionsButton;

    UPROPERTY(meta = (BindWidget))
    UButton* QuitButton;

    UPROPERTY(meta = (BindWidget))
    UWidgetSwitcher* MenuSwitcher;

private:
    UFUNCTION()
    void OnStartClicked();

    UFUNCTION()
    void OnQuitClicked();

    UFUNCTION()
    void OnChooseLevelClicked();

    UFUNCTION() 
    void OnOptionsClicked();
};
