// LevelSelectWidget.cpp

#include "LevelSelectWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"

void ULevelSelectWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (Level1Button)
    {
        Level1Button->OnClicked.AddDynamic(this, &ULevelSelectWidget::OnLevel1Clicked);
    }
    if (Level2Button)
    {
        Level2Button->OnClicked.AddDynamic(this, &ULevelSelectWidget::OnLevel2Clicked);
    }
    if (Level3Button)
    {
        Level3Button->OnClicked.AddDynamic(this, &ULevelSelectWidget::OnLevel3Clicked);
    }
    if (Level4Button)
    {
        Level4Button->OnClicked.AddDynamic(this, &ULevelSelectWidget::OnLevel4Clicked);
    }
    if (Level5Button)
    {
        Level5Button->OnClicked.AddDynamic(this, &ULevelSelectWidget::OnLevel5Clicked);
    }

    if (BackButton)
    {
        BackButton->OnClicked.AddDynamic(this, &ULevelSelectWidget::OnBackClicked);
    }
}

void ULevelSelectWidget::OnLevel1Clicked()
{
    UGameplayStatics::OpenLevel(this, TEXT("Level_1"));
}

void ULevelSelectWidget::OnLevel2Clicked()
{
    UGameplayStatics::OpenLevel(this, TEXT("Level_2"));
}

void ULevelSelectWidget::OnLevel3Clicked()
{
    UGameplayStatics::OpenLevel(this, TEXT("Level_3"));
}

void ULevelSelectWidget::OnLevel4Clicked()
{
    UGameplayStatics::OpenLevel(this, TEXT("Level_4"));
}

void ULevelSelectWidget::OnLevel5Clicked()
{
    UGameplayStatics::OpenLevel(this, TEXT("Level_5"));
}

void ULevelSelectWidget::OnBackClicked()
{
    if (UWidget* Parent = GetParent())
    {
        if (UWidgetSwitcher* Switcher = Cast<UWidgetSwitcher>(Parent))
        {
            Switcher->SetActiveWidgetIndex(0);
            return;
        }
    }
    UGameplayStatics::OpenLevel(this, TEXT("MainMenuMap"));
}

