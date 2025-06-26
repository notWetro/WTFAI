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

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void HandleAttack();

    void Die();

    FTimerHandle AttackTimerHandle;

public:
    virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
                             AController* EventInstigator, AActor* DamageCauser) override;

    UPROPERTY(EditDefaultsOnly, Category = "Combat")
    TSubclassOf<AActor> ProjectileClass;

    UPROPERTY(EditDefaultsOnly, Category = "Combat")
    float AttackInterval = 3.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Combat")
    float MaxHealth = 30.0f;

    float CurrentHealth;
};
