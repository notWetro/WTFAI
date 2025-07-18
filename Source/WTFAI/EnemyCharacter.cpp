#include "EnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "Components/CapsuleComponent.h"


AEnemyCharacter::AEnemyCharacter()
{
    PrimaryActorTick.bCanEverTick = false;
    PrimaryActorTick.bCanEverTick = true;
    
    GetCapsuleComponent()->SetCollisionObjectType(ECC_Pawn);
    GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
}

void AEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();
    
    CurrentHealth = MaxHealth;
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
    
    GetMesh()->PlayAnimation(AttackAnim, false);

    GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &AEnemyCharacter::HandleAttack, AttackInterval, true);
}

void AEnemyCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsPlayingNonLoopingAnimation)
        return;

    if (GetVelocity().Size() > 10.f && WalkForwardAnim && GetMesh())
    {
        if (!GetMesh()->IsPlaying())
        {
            GetMesh()->PlayAnimation(WalkForwardAnim, true);
        }
    }
}

void AEnemyCharacter::HandleAttack()
{
    AActor* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (!Player || !ProjectileClass) return;

    FVector Start = GetActorLocation() + FVector(0, 0, 40.f);
    FVector Direction = (Player->GetActorLocation() - Start).GetSafeNormal();
    Direction.Z = 0;
    FRotator SpawnRotation = Direction.Rotation();

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;

    GetWorld()->SpawnActor<AActor>(ProjectileClass, Start, SpawnRotation, SpawnParams);
    
    if (AttackAnim && GetMesh() && !bIsDying)
    {
        GetMesh()->PlayAnimation(AttackAnim, false);
    }
    if (EnemyAttackAbilitySound)
    {
        UGameplayStatics::PlaySoundAtLocation(this, EnemyAttackAbilitySound, GetActorLocation());
    }
}

float AEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
                                  AController* EventInstigator, AActor* DamageCauser)
{
    CurrentHealth -= DamageAmount;

    if (CurrentHealth <= 0.f)
    {
        Die();
        return DamageAmount;
    }
    
    if (GetHitAnim && GetMesh() && !bIsDying)
    {
        GetMesh()->PlayAnimation(GetHitAnim, false);
    }

    return DamageAmount;
}

void AEnemyCharacter::Die()
{
    if (bIsDying) return;
    bIsDying = true;
    
    GetWorldTimerManager().ClearTimer(AttackTimerHandle);

    if (DieAnim && GetMesh())
    {
        GetMesh()->PlayAnimation(DieAnim, false);
        // Delay before Destroy
        GetWorldTimerManager().SetTimerForNextTick([this]()
        {
            SetLifeSpan(0.8f);
        });
    }
    else
    {
        Destroy();
    }
}
