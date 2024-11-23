// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_Fps_Shooter.h"
#include "FPS_Shooter/Character/BlasterCharacter.h"
#include "FPS_Shooter/PlayerController/BlasterPlayerController.h"

void AGM_Fps_Shooter::PlayerEliminated(ABlasterCharacter* ElimanatedCharacter, ABlasterPlayerController* VictimController, ABlasterPlayerController* AttackerController)
{
	if (ElimanatedCharacter) {
		ElimanatedCharacter->Elim();
	}
}
