#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PortalActor.generated.h"

UCLASS()
class WTFAI_API APortalActor : public AActor
{
    GENERATED_BODY()
    
public:
    // Konstruktor
    APortalActor();
    
    // Mesh Komponente
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UStaticMeshComponent* PortalMesh;

    // Collider Komponente
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class USphereComponent* CollisionSphere;

    // Overlap Funktion
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
                       AActor* OtherActor,
                       UPrimitiveComponent* OtherComp,
                       int32 OtherBodyIndex,
                       bool bFromSweep,
                       const FHitResult& SweepResult);

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
};
