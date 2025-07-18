#include "PortalActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "WTFAICharacter.h"
#include "WTFAIPlayerController.h"

APortalActor::APortalActor()
{
    PrimaryActorTick.bCanEverTick = false;

    // Mesh-Komponente
    PortalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalMesh"));
    RootComponent = PortalMesh;

    // Collider-Komponente
    CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
    CollisionSphere->SetupAttachment(RootComponent);
    CollisionSphere->SetSphereRadius(100.f);

    CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &APortalActor::OnOverlapBegin);
}

void APortalActor::BeginPlay()
{
    Super::BeginPlay();
}

void APortalActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
                                  AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp,
                                  int32 OtherBodyIndex,
                                  bool bFromSweep,
                                  const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor != this))
    {
        if (Cast<AWTFAICharacter>(OtherActor))
        {
            if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
            {
                if (AWTFAIPlayerController* MyPC = Cast<AWTFAIPlayerController>(PC))
                {
                    if (LevelUpSound)
                    {
                        UGameplayStatics::PlaySound2D(this, LevelUpSound);
                    }
                    MyPC->ShowLevelSelect();
                }
            }
        }
    }
}
