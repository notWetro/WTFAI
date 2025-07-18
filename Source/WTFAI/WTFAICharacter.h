#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WTFAICharacter.generated.h"

UCLASS(Blueprintable)
class AWTFAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AWTFAICharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
    
    // Angriff (Magie-Projektil)
    UPROPERTY(EditDefaultsOnly, Category = "Combat")
    TSubclassOf<AActor> ProjectileClass;

    UPROPERTY(EditDefaultsOnly, Category = "Combat")
    float AttackCooldown = 0.1f;

    void HandleAttack();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    class UAnimMontage* CastAnimation;
    
    
    virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

    void Die();
    
    //Leben und Lebensanzeige
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float MaxHealth = 100.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
    float CurrentHealth;
    
    UFUNCTION(BlueprintCallable, Category = "Stats")
    float GetMaxHealth() const;
    float GetCurrentHealth() const;

    //Mana
    float GetManaPercent() const;
    float GetMaxMana() const;
    float GetCurrentMana() const;
    bool HasEnoughMana(float Cost) const;
    void ConsumeMana(float Cost);
    void RegenerateMana(float DeltaTime);
    
    UPROPERTY(EditDefaultsOnly, Category = "Stats")
    float MaxMana = 100.0f;

    UPROPERTY(VisibleAnywhere, Category = "Stats")
    float CurrentMana;

    // Jump sound effect 
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
    USoundBase* JumpSound = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
    USoundBase* LowManaSound = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
    USoundBase* TakeDamageSound = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
    USoundBase* AttackSound = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
    USoundBase* AttackAbilitySound = nullptr;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
    
protected:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void MoveForward(float Value);
    void MoveRight(float Value);
    void StartJump();
    void StopJump();   

    float LastAttackTime = -100.0f;
    
    virtual void BeginPlay() override;
};
