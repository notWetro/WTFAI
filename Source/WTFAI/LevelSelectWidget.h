#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelSelectWidget.generated.h"

class UButton;

UCLASS()
class WTFAI_API ULevelSelectWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;

    /** Buttons for each level (add more as needed) */
    UPROPERTY(meta = (BindWidget))
    UButton* Level1Button;

    UPROPERTY(meta = (BindWidget))
    UButton* Level2Button;

    UPROPERTY(meta = (BindWidget))
    UButton* Level3Button;

    UPROPERTY(meta = (BindWidget))
    UButton* Level4Button;

    UPROPERTY(meta = (BindWidget))
    UButton* Level5Button;

    /** Back button to return to the parent menu */
    UPROPERTY(meta = (BindWidget))
    UButton* BackButton;

private:
    UFUNCTION()
    void OnLevel1Clicked();

    UFUNCTION()
    void OnLevel2Clicked();

    UFUNCTION()
    void OnLevel3Clicked();

    UFUNCTION()
    void OnLevel4Clicked();

    UFUNCTION()
    void OnLevel5Clicked();

    UFUNCTION()
    void OnBackClicked();
};
