// Copyright Epic Games, Inc. All Rights Reserved.

#include "WTFAIGameMode.h"
#include "WTFAIPlayerController.h"
#include "WTFAICharacter.h"
#include "wtfaiHUD.h"
#include "UObject/ConstructorHelpers.h"

AWTFAIGameMode::AWTFAIGameMode()
{
    
    //Lebensanzeige
    HUDClass = AwtfaiHUD::StaticClass();
    
	// use our custom PlayerController class
	PlayerControllerClass = AWTFAIPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter.BP_TopDownCharacter_C"));
	if (PlayerPawnBPClass.Succeeded())
	{
		UE_LOG(LogTemp, Log, TEXT("✅ Found TopDownCharacter Blueprint."));
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("❌ Failed to find TopDownCharacter at path: %s"),
			TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter.BP_TopDownCharacter_C"));
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(
		TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController.BP_TopDownPlayerController_C")
	);
	if (PlayerControllerBPClass.Succeeded())
	{
		UE_LOG(LogTemp, Log, TEXT("✅ Found TopDownPlayerController Blueprint."));
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("❌ Failed to find TopDownPlayerController at path: %s"),
			TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController.BP_TopDownPlayerController_C"));
	}
}
