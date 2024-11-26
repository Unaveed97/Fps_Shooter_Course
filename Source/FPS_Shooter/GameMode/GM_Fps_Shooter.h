// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GM_Fps_Shooter.generated.h"

/**
 * 
 */
UCLASS()
class FPS_SHOOTER_API AGM_Fps_Shooter : public AGameMode
{
	GENERATED_BODY()
	
public:
	virtual void PlayerEliminated(class ABlasterCharacter* ElimanatedCharacter, class ABlasterPlayerController* VictimController, class ABlasterPlayerController* AttackerController);
	virtual void RequestRespawn(class ACharacter* ElimnedCharacter, class AController* ElimnedController);
};
