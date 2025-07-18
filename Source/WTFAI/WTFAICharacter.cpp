#include "WTFAICharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "WTFAIPlayerController.h"
#include "Kismet/GameplayStatics.h"


AWTFAICharacter::AWTFAICharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
  
    GetCapsuleComponent()->SetCollisionObjectType(ECC_Pawn);
    GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
    GetCharacterMovement()->JumpZVelocity = 600.f;
    GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false;

	// Create a camera
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
    
    static ConstructorHelpers::FClassFinder<AActor> ProjectileBP(TEXT("/Game/Blueprints/BP_MagicProjectile"));
    if (ProjectileBP.Succeeded())
    {
        ProjectileClass = ProjectileBP.Class;
    }
    
    CurrentMana = MaxMana;
}

void AWTFAICharacter::BeginPlay()
{
    Super::BeginPlay();
    CurrentHealth = MaxHealth;
}

void AWTFAICharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    RegenerateMana(DeltaSeconds);
}

void AWTFAICharacter::MoveForward(float Value)
{
    if (Controller && Value != 0.0f)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void AWTFAICharacter::MoveRight(float Value)
{
    if (Controller && Value != 0.0f)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(Direction, Value);
    }
}

void AWTFAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &AWTFAICharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AWTFAICharacter::MoveRight);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AWTFAICharacter::StartJump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &AWTFAICharacter::StopJump);
    PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AWTFAICharacter::HandleAttack);
}

void AWTFAICharacter::StartJump()
{
    if (JumpSound)
    {
        UGameplayStatics::PlaySoundAtLocation(this, JumpSound, GetActorLocation());
    }
    Jump();
}

void AWTFAICharacter::StopJump()
{
    StopJumping();
}

void AWTFAICharacter::HandleAttack()
{
    if (!ProjectileClass) return;
    
    float CurrentTime = GetWorld()->GetTimeSeconds();
    if (CurrentTime - LastAttackTime < AttackCooldown) return;
    
    //Mana handling
    float ManaCost = 20.0f;
    if (!HasEnoughMana(ManaCost))
    {
        if (LowManaSound)
        {
            UGameplayStatics::PlaySoundAtLocation(this, LowManaSound, GetActorLocation());
        }
        UE_LOG(LogTemp, Warning, TEXT("Nicht genug Mana!"));
        return;
    }
    
    APlayerController* PC = Cast<APlayerController>(GetController());
    if (!PC) return;
    
    FHitResult Hit;
    if (PC->GetHitResultUnderCursor(ECC_Visibility, false, Hit))
    {
        FVector SpawnLocation = GetActorLocation() + FVector(0, 0, 40.f);
        FVector TargetLocation = Hit.ImpactPoint;
        
        FVector Direction = (TargetLocation - SpawnLocation);
        
        Direction.Z = 0; // Nur horizontale Richtung beachten
        
        if (Direction.IsNearlyZero())
        {
            Direction = FVector::ForwardVector; // Fallback, falls Richtung Null
        }
        else
        {
            Direction.Normalize();
        }
        
        FRotator SpawnRotation = Direction.Rotation();
        
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
        
        AActor* SpawnedProjectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
        if (SpawnedProjectile)
        {
            if (CastAnimation)
            {
                PlayAnimMontage(CastAnimation);
            }
            
            LastAttackTime = CurrentTime;
            ConsumeMana(ManaCost);
        }
    }
}

float AWTFAICharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    float DamageApplied = FMath::Min(CurrentHealth, DamageAmount);
    CurrentHealth -= DamageApplied;
    if (TakeDamageSound)
    {
        UGameplayStatics::PlaySoundAtLocation(this, TakeDamageSound, GetActorLocation());
    }

    if (CurrentHealth <= 0.f)
    {
        Die();
    }

    return DamageApplied;
}

float AWTFAICharacter::GetMaxHealth() const
{
    return MaxHealth;
}

float AWTFAICharacter::GetCurrentHealth() const
{
    return CurrentHealth;
}

void AWTFAICharacter::Die()
{
    // Disable further input/movement
    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        PC->DisableInput(PC);
    }

    // show the Death Screen
    if (AWTFAIPlayerController* MyPC = Cast<AWTFAIPlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
    {
        MyPC->ShowDeathScreen();
    }
    else
    {
        //just pause if we can’t get our controller
        UGameplayStatics::SetGamePaused(this, true);
    }

    // hide, destroy the pawn mesh so the player cant move/see the corpse
    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);
}


float AWTFAICharacter::GetManaPercent() const
{
    return CurrentMana / MaxMana;
}

float AWTFAICharacter::GetMaxMana() const
{
    return MaxMana;
}

float AWTFAICharacter::GetCurrentMana() const
{
    return CurrentMana;
}

bool AWTFAICharacter::HasEnoughMana(float Cost) const
{
    return CurrentMana >= Cost;
}

void AWTFAICharacter::ConsumeMana(float Cost)
{
    CurrentMana = FMath::Clamp(CurrentMana - Cost, 0.0f, MaxMana);
}

void AWTFAICharacter::RegenerateMana(float DeltaTime)
{
    CurrentMana = FMath::Clamp(CurrentMana + (30.0f * DeltaTime), 0.0f, MaxMana);
}
