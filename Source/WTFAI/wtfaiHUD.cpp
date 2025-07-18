#include "wtfaiHUD.h"
#include "WTFAICharacter.h"
#include "Engine/Canvas.h"
#include "UObject/ConstructorHelpers.h"

void AwtfaiHUD::DrawHUD()
{
    Super::DrawHUD();

    DrawHealthBar();
    DrawManaBar();
}

void AwtfaiHUD::DrawHealthBar()
{
    AWTFAICharacter* MyChar = Cast<AWTFAICharacter>(GetOwningPawn());
    if (!MyChar) return;

    float MaxHealth = MyChar->GetMaxHealth();
    float CurrentHealth = MyChar->GetCurrentHealth();
    float HealthPercent = CurrentHealth / MaxHealth;

    // Leistenparameter
    const float BarWidth = 300.0f;
    const float BarHeight = 25.0f;
    const float Padding = 2.0f;
    const float ScreenX = 40.0f;
    const float ScreenY = 40.0f;

    // Hintergrund
    FLinearColor BackgroundColor = FLinearColor(0.1f, 0.1f, 0.1f, 1.0f);
    DrawRect(BackgroundColor, ScreenX, ScreenY, BarWidth, BarHeight);

    // Dynamische Füllfarbe: grün → gelb → rot
    FLinearColor HealthColor = FLinearColor::LerpUsingHSV(FLinearColor::Red, FLinearColor::Green, HealthPercent);

    float FilledWidth = BarWidth * HealthPercent;
    DrawRect(HealthColor, ScreenX, ScreenY, FilledWidth, BarHeight);

    // Lebensanzeige als Text
    FString HealthText = FString::Printf(TEXT("HP: %d / %d"), FMath::RoundToInt(CurrentHealth), FMath::RoundToInt(MaxHealth));
    FCanvasTextItem TextItem(FVector2D(ScreenX + Padding, ScreenY + BarHeight / 2), FText::FromString(HealthText), GEngine->GetSmallFont(), FLinearColor::Black);
    TextItem.bCentreY = true;
    TextItem.bCentreX = false;
    Canvas->DrawItem(TextItem);
}

void AwtfaiHUD::DrawManaBar()
{
    AWTFAICharacter* MyChar = Cast<AWTFAICharacter>(GetOwningPawn());
    if (!MyChar) return;

    float ManaPercent = MyChar->GetManaPercent();
    float MaxMana = MyChar->GetMaxMana();
    float CurrentMana = MyChar->GetCurrentMana();

    const float BarWidth = 200.0f;
    const float BarHeight = 20.0f;
    const float Padding = 2.0f;
    const float ScreenX = 40.0f;
    const float ScreenY = 75.0f;

    FLinearColor BackgroundColor = FLinearColor::Black;
    DrawRect(BackgroundColor, ScreenX, ScreenY, BarWidth, BarHeight);

    FLinearColor ManaColor = FLinearColor::Blue;
    float FilledWidth = BarWidth * ManaPercent;
    DrawRect(ManaColor, ScreenX, ScreenY, FilledWidth, BarHeight);
    
    // Manaanzeige als Text
    FString ManaText = FString::Printf(TEXT("MP: %d / %d"), FMath::RoundToInt(CurrentMana), FMath::RoundToInt(MaxMana));
    FCanvasTextItem TextItem(FVector2D(ScreenX + Padding, ScreenY + BarHeight / 2), FText::FromString(ManaText), GEngine->GetSmallFont(), FLinearColor::White);
    TextItem.bCentreY = true;
    TextItem.bCentreX = false;
    Canvas->DrawItem(TextItem);
}
