#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "wtfaiHUD.generated.h"

UCLASS()
class WTFAI_API AwtfaiHUD : public AHUD
{
	GENERATED_BODY()
    
public:
    virtual void DrawHUD() override;
    
private:
    void DrawHealthBar();

};
