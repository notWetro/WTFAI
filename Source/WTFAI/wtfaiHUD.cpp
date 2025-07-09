#include "wtfaiHUD.h"
#include "WTFAICharacter.h"
#include "Engine/Canvas.h"
#include "UObject/ConstructorHelpers.h"

void AwtfaiHUD::DrawHUD()
{
    Super::DrawHUD();

    DrawHealthBar();
}

void AwtfaiHUD::DrawHealthBar()
{
    AWTFAICharacter* MyChar = Cast<AWTFAICharacter>(GetOwningPawn());
    if (!MyChar) return;

    float HealthPercent = MyChar->GetHealthPercent();

    // Leistenparameter
    const float BarWidth = 300.0f;
    const float BarHeight = 25.0f;
    const float Padding = 2.0f;
    const float ScreenX = Canvas->SizeX / 2 - BarWidth / 2;
    const float ScreenY = Canvas->SizeY - 80.0f;

    // Hintergrund
    FLinearColor BackgroundColor = FLinearColor(0.1f, 0.1f, 0.1f, 1.0f);
    DrawRect(BackgroundColor, ScreenX, ScreenY, BarWidth, BarHeight);

    // Dynamische Füllfarbe: grün → gelb → rot
    FLinearColor HealthColor = FLinearColor::LerpUsingHSV(FLinearColor::Red, FLinearColor::Green, HealthPercent);

    // Füllung
    float FilledWidth = BarWidth * HealthPercent;
    DrawRect(HealthColor, ScreenX, ScreenY, FilledWidth, BarHeight);

    // Lebensanzeige als Text
    FString HealthText = FString::Printf(TEXT("HP"), FMath::RoundToInt(HealthPercent * 100));
    FCanvasTextItem TextItem(FVector2D(ScreenX + BarWidth / 2, ScreenY + BarHeight / 2), FText::FromString(HealthText), GEngine->GetSmallFont(), FLinearColor::White);
    TextItem.bCentreX = true;
    TextItem.bCentreY = true;
    Canvas->DrawItem(TextItem);
}
