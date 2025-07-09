#include "MagicProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

AMagicProjectile::AMagicProjectile()
{
    PrimaryActorTick.bCanEverTick = true;

    // Collision
    CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
    CollisionComp->InitSphereRadius(10.f);
    CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    CollisionComp->SetCollisionObjectType(ECC_GameTraceChannel1); // "Projectile"
    CollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
    CollisionComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
    CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AMagicProjectile::OnOverlap);
    RootComponent = CollisionComp;

    // Mesh (optional sichtbar)
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
    MeshComponent->SetupAttachment(RootComponent);
    MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("VFX"));
    ParticleSystem->SetupAttachment(RootComponent);

    // Bewegung
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->InitialSpeed = 1200.f;
    ProjectileMovement->MaxSpeed = 1200.f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->ProjectileGravityScale = 0.f;

    // Lebensdauer
    InitialLifeSpan = LifeSpanSeconds;
}

void AMagicProjectile::BeginPlay()
{
    Super::BeginPlay();
    
    StartLocation = GetActorLocation();

    // Eigener Owner wird ignoriert bei Bewegung
    if (GetOwner())
    {
        CollisionComp->IgnoreActorWhenMoving(GetOwner(), true);
    }
}

void AMagicProjectile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    float DistanceTravelled = FVector::Dist(StartLocation, GetActorLocation());

    if (DistanceTravelled >= MaxTravelDistance)
    {
        Destroy();
    }
}

void AMagicProjectile::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                 bool bFromSweep, const FHitResult& SweepResult)
{
    if (!OtherActor || OtherActor == this || OtherActor == GetOwner())
        return;

    // Schaden anwenden
    UGameplayStatics::ApplyDamage(OtherActor, Damage, GetInstigatorController(), this, nullptr);

    // Komponenten unsichtbar machen
    MeshComponent->SetVisibility(false, true);
    ParticleSystem->SetVisibility(false, true);

    Destroy();
}
