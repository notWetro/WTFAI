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
    RemoveFromParent();
}

