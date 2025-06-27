#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UButton;

UCLASS()
class WTFAI_API UMainMenuWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    // Called after Slate widget hierarchy is constructed
    virtual void NativeConstruct() override;

    // These will hook up to your UMG buttons by name
    UPROPERTY(meta = (BindWidget))
    UButton* StartButton;

    UPROPERTY(meta = (BindWidget))
    UButton* QuitButton;

private:
    UFUNCTION()
    void OnStartClicked();

    UFUNCTION()
    void OnQuitClicked();
};
