#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingHintActor.generated.h"

class UTextRenderComponent;
class UBoxComponent;

UCLASS()
class WTFAI_API AFloatingHintActor : public AActor
{
    GENERATED_BODY()

public:
    AFloatingHintActor();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hint")
    FString HintText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hint")
    float FloatSpeed = 20.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hint")
    bool bFloatText = true;

private:
    UPROPERTY(VisibleAnywhere)
    UTextRenderComponent* TextComponent;
};
