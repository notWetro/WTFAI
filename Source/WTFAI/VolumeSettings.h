#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "VolumeSettings.generated.h"

UCLASS()
class WTFAI_API UVolumeSettings : public USaveGame
{
    GENERATED_BODY()
public:
    UPROPERTY(VisibleAnywhere, Category = "Settings")
    float MasterVolume = 1.0f;
};
