#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenuWidget.generated.h"

class UButton;

UCLASS()
class WTFAI_API UPauseMenuWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    // Called once the UI is constructed
    virtual void NativeConstruct() override;

    // Bound widgets (must match names in UMG)
    UPROPERTY(meta = (BindWidget))
    UButton* ResumeButton;

    UPROPERTY(meta = (BindWidget))
    UButton* QuitToMenuButton;

private:
    // Handlers for the buttons
    UFUNCTION()
    void OnResumeClicked();

    UFUNCTION()
    void OnQuitToMenuClicked();
};
