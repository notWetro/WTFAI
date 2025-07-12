#include "OptionsWidget.h"
#include "VolumeSettings.h"
#include "Components/Slider.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"

void UOptionsWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // 1) Load saved volume
    const FString SlotName = TEXT("VolumeSettings");
    const uint32 UserIndex = 0;
    if (USaveGame* SG = UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex))
    {
        if (UVolumeSettings* VS = Cast<UVolumeSettings>(SG))
        {
            float SavedVol = FMath::Clamp(VS->MasterVolume, 0.f, 1.f);
            if (MasterSoundMix && MasterSoundClass)
            {
                UGameplayStatics::SetSoundMixClassOverride(
                    this, MasterSoundMix, MasterSoundClass,
                    SavedVol, 
                    1.f,
                    0.f, 
                    true      
                );
                UGameplayStatics::PushSoundMixModifier(this, MasterSoundMix);
            }
            if (MasterVolumeSlider)
                MasterVolumeSlider->SetValue(SavedVol);
        }
    }

    // 2) Bind slider and Back button
    if (MasterVolumeSlider)
        MasterVolumeSlider->OnValueChanged.AddDynamic(this, &UOptionsWidget::OnMasterVolumeChanged);

    if (BackButton)
        BackButton->OnClicked.AddDynamic(this, &UOptionsWidget::OnBackClicked);
}

void UOptionsWidget::OnMasterVolumeChanged(float NewValue)
{
    NewValue = FMath::Clamp(NewValue, 0.f, 1.f);

    if (MasterSoundMix && MasterSoundClass)
    {
        UGameplayStatics::SetSoundMixClassOverride(
            this, MasterSoundMix, MasterSoundClass,
            NewValue, 1.f, 0.f, true
        );
        UGameplayStatics::PushSoundMixModifier(this, MasterSoundMix);
    }

    // Save immediately
    const FString SlotName = TEXT("VolumeSettings");
    const uint32 UserIndex = 0;
    if (UVolumeSettings* VS = Cast<UVolumeSettings>(
        UGameplayStatics::CreateSaveGameObject(UVolumeSettings::StaticClass())))
    {
        VS->MasterVolume = NewValue;
        UGameplayStatics::SaveGameToSlot(VS, SlotName, UserIndex);
    }
}

void UOptionsWidget::OnBackClicked()
{
    // Flip back to main-menu in the switcher
    if (UPanelWidget* Parent = GetParent())
        if (UWidgetSwitcher* S = Cast<UWidgetSwitcher>(Parent))
        {
            S->SetActiveWidgetIndex(0);
            return;
        }

    RemoveFromParent();
}
