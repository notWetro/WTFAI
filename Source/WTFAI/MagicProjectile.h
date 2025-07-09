#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MagicProjectile.generated.h"

UCLASS()
class WTFAI_API AMagicProjectile : public AActor
{
    GENERATED_BODY()
    
public:
    AMagicProjectile();
    
protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

private:
    UFUNCTION()
    void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                   bool bFromSweep, const FHitResult& SweepResult);

    UPROPERTY(EditDefaultsOnly, Category = "Combat")
    float MaxTravelDistance = 625.0f;

    FVector StartLocation;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    class USphereComponent* CollisionComp;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UProjectileMovementComponent* ProjectileMovement;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UParticleSystemComponent* ParticleSystem;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UStaticMeshComponent* MeshComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Combat")
    float Damage = 10.f;

    UPROPERTY(EditDefaultsOnly, Category = "Combat")
    float LifeSpanSeconds = 3.0f;
};
