#include "DeathZone.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "WTFAICharacter.h" // <-- Passe das ggf. auf deinen Charakterklassennamen an
#include "Kismet/GameplayStatics.h"

ADeathZone::ADeathZone()
{
    PrimaryActorTick.bCanEverTick = false;

    TriggerZone = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerZone"));
    RootComponent = TriggerZone;

    TriggerZone->SetBoxExtent(FVector(5000.0f, 5000.0f, 100.0f));
    TriggerZone->SetCollisionProfileName(TEXT("Trigger"));
    TriggerZone->SetGenerateOverlapEvents(true);

    TriggerZone->OnComponentBeginOverlap.AddDynamic(this, &ADeathZone::OnOverlapBegin);
}

void ADeathZone::BeginPlay()
{
    Super::BeginPlay();
}

void ADeathZone::OnOverlapBegin(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult
)
{
    if (AWTFAICharacter* Character = Cast<AWTFAICharacter>(OtherActor))
    {
        Character->Die();
    }
}
