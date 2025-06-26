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
    CollisionComp->SetCollisionProfileName("BlockAll");
    CollisionComp->OnComponentHit.AddDynamic(this, &AMagicProjectile::OnHit);
    RootComponent = CollisionComp;

    // Mesh
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
    MeshComponent->SetupAttachment(RootComponent);
    MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision); // Kein Konflikt mit CollisionComp
    
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

    //Kollisionsebenen, damit nicht mit Player kolidiert
    CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    CollisionComp->SetCollisionObjectType(ECC_GameTraceChannel1); // z.B. ein eigener Channel für Projektile
    CollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
    CollisionComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
    CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap); // nur Gegner treffen

}

void AMagicProjectile::BeginPlay()
{
    Super::BeginPlay();
    if (GetOwner())
    {
        CollisionComp->IgnoreActorWhenMoving(GetOwner(), true);
    }

}

void AMagicProjectile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (InitialLifeSpan == 0.f)
    {
        Destroy();
    }
}

void AMagicProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
                             UPrimitiveComponent* OtherComp, FVector NormalImpulse,
                             const FHitResult& Hit)
{
    if (OtherActor && OtherActor != this && OtherActor != GetOwner())
    {
        UGameplayStatics::ApplyDamage(OtherActor, Damage, nullptr, this, nullptr);
    }

    Destroy(); // zerstört das Projektil nach dem Treffer
}
