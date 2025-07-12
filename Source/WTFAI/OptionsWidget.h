#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Slider.h"
#include "Components/Button.h"
#include "Sound/SoundMix.h"
#include "Sound/SoundClass.h"
#include "OptionsWidget.generated.h"

UCLASS()
class WTFAI_API UOptionsWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

protected:
    UPROPERTY(meta = (BindWidget))
    USlider* MasterVolumeSlider;

    UPROPERTY(meta = (BindWidget))
    UButton* BackButton;

    UPROPERTY(EditAnywhere, Category = "Audio")
    USoundMix* MasterSoundMix;

    UPROPERTY(EditAnywhere, Category = "Audio")
    USoundClass* MasterSoundClass;

private:
    UFUNCTION()
    void OnMasterVolumeChanged(float NewValue);

    UFUNCTION()
    void OnBackClicked();
};
