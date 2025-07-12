#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class WTFAI_API AEnemyCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AEnemyCharacter();
    
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

protected:

    UFUNCTION()
    void HandleAttack();

    void Die();

    FTimerHandle AttackTimerHandle;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
    UAnimSequence* WalkForwardAnim;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
    UAnimSequence* AttackAnim;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
    UAnimSequence* GetHitAnim;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
    UAnimSequence* DieAnim;
    
    UPROPERTY()
    bool bIsPlayingWalkAnim = false;
    
    UPROPERTY()
    bool bIsPlayingNonLoopingAnimation = false;

public:
    virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
                             AController* EventInstigator, AActor* DamageCauser) override;

    UPROPERTY(EditDefaultsOnly, Category = "Combat")
    TSubclassOf<AActor> ProjectileClass;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float WalkSpeed = 200.0f; // Standard ist 600.f

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float AttackInterval = 3.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float MaxHealth = 60.0f;

    float CurrentHealth;
};
