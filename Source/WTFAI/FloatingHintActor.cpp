#include "FloatingHintActor.h"
#include "Components/TextRenderComponent.h"

AFloatingHintActor::AFloatingHintActor()
{
    PrimaryActorTick.bCanEverTick = true;

    TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextComponent"));
    RootComponent = TextComponent;

    TextComponent->SetHorizontalAlignment(EHTA_Center);
    TextComponent->SetWorldSize(50.f);
    TextComponent->SetTextRenderColor(FColor::Yellow);
}

void AFloatingHintActor::BeginPlay()
{
    Super::BeginPlay();

    TextComponent->SetText(FText::FromString(HintText));
}

void AFloatingHintActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bFloatText)
    {
        FVector NewLocation = GetActorLocation();
        NewLocation.Z += FMath::Sin(GetWorld()->TimeSeconds * 2.0f) * FloatSpeed * DeltaTime;
        SetActorLocation(NewLocation);
    }
}
