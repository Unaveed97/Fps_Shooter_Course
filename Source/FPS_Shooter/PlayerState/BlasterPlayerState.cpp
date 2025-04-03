// Fill out your copyright notice in the Description page of Project Settings.


#include "BlasterPlayerState.h"
#include "FPS_Shooter/Character/BlasterCharacter.h"
#include "FPS_Shooter/PlayerController/BlasterPlayerController.h"
#include "Net/UnrealNetwork.h"


void ABlasterPlayerState::AddToScore(float ScoreAmount)
{
	//Score += ScoreAmount;
	SetScore(GetScore() + ScoreAmount);
	Character = Character == nullptr ? Cast<ABlasterCharacter>(GetPawn()) : Character;

	if (Character) {
		Controller = Controller == nullptr ? Cast<ABlasterPlayerController>(Character->Controller) : Controller;
		if (Controller) {
			Controller->SetHUDScore(GetScore());
		}
	} 
}

void ABlasterPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABlasterPlayerState, Defeats);
	DOREPLIFETIME(ABlasterPlayerState, KilledBy);
}

void ABlasterPlayerState::OnRep_Score()
{
	Super::OnRep_Score();
	
	Character = Character == nullptr ? Cast<ABlasterCharacter>(GetPawn()) : Character;

	if (Character) {
		Controller = Controller == nullptr ? Cast<ABlasterPlayerController>(Character->Controller) : Controller;
		if (Controller) {
			Controller->SetHUDScore(GetScore());
		}
	}
}

void ABlasterPlayerState::AddToDefeats(int32 DefeatsAmount)
{
	Defeats += DefeatsAmount;
	Character = Character == nullptr ? Cast<ABlasterCharacter>(GetPawn()) : Character;

	if (Character) {
		Controller = Controller == nullptr ? Cast<ABlasterPlayerController>(Character->Controller) : Controller;
		if (Controller) {
			Controller->SetHUDDefeats(Defeats);
		}
	}
}

void ABlasterPlayerState::UpdateDeathMessage(FString KillerName)
{
	KilledBy = KillerName;
	UpdateDeathMessageHUD();
}

void ABlasterPlayerState::UpdateDeathMessageHUD()
{
	Character = Character == nullptr ? Cast<ABlasterCharacter>(GetPawn()) : Character;
	if (Character)
	{
		Controller = Controller == nullptr ? Cast<ABlasterPlayerController>(Character->Controller) : Controller;
		if (Controller) {
			Controller->UpdateDeathMessage(KilledBy);
		}
	}
}

void ABlasterPlayerState::OnRep_Defeats()
{
	Character = Character == nullptr ? Cast<ABlasterCharacter>(GetPawn()) : Character;
	if (Character) {
		Controller = Controller == nullptr ? Cast<ABlasterPlayerController>(Character->Controller) : Controller;
		if (Controller) {
			Controller->SetHUDDefeats(Defeats);
		}
	}
}

void ABlasterPlayerState::OnRep_KilledBy()
{
	UpdateDeathMessageHUD();
}
