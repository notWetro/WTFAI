#include "EnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"

AEnemyCharacter::AEnemyCharacter()
{
    PrimaryActorTick.bCanEverTick = false;
    CurrentHealth = MaxHealth;
    
    GetCharacterMovement()->MaxWalkSpeed = 200.f; // Standard ist 600.f
}

void AEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();

    GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &AEnemyCharacter::HandleAttack, AttackInterval, true);
}

void AEnemyCharacter::HandleAttack()
{
    AActor* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (!Player || !ProjectileClass) return;

    FVector Start = GetActorLocation() + FVector(0, 0, 60.f);
    FVector Direction = (Player->GetActorLocation() - Start).GetSafeNormal();
    Direction.Z = 0;
    FRotator SpawnRotation = Direction.Rotation();

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;

    GetWorld()->SpawnActor<AActor>(ProjectileClass, Start, SpawnRotation, SpawnParams);
}

float AEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
                                  AController* EventInstigator, AActor* DamageCauser)
{
    CurrentHealth -= DamageAmount;

    if (CurrentHealth <= 0.f)
    {
        Die();
    }

    return DamageAmount;
}

void AEnemyCharacter::Die()
{
    GetWorldTimerManager().ClearTimer(AttackTimerHandle);
    Destroy();
}
