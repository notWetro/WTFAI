#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

UCLASS()
class DEINPROJECTNAME_API UMainMenuWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual bool Initialize() override;

protected:
    UPROPERTY(meta = (BindWidget))
    class UButton* PlayButton;

    UPROPERTY(meta = (BindWidget))
    class UButton* QuitButton;

    UFUNCTION()
    void OnPlayClicked();

    UFUNCTION()
    void OnQuitClicked();
};
