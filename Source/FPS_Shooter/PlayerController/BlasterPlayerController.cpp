// Fill out your copyright notice in the Description page of Project Settings.


#include "BlasterPlayerController.h"
#include "FPS_Shooter/HUD/BlasterHUD.h"
#include "FPS_Shooter/HUD/CharacterOverlay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "FPS_Shooter/Character/BlasterCharacter.h"

void ABlasterPlayerController::BeginPlay() {
	Super::BeginPlay();

	BlasterHUD = Cast<ABlasterHUD>(GetHUD());
}

void ABlasterPlayerController::SetHUDHealth(float Health, float MaxHealth) {
	
	BlasterHUD = BlasterHUD == nullptr ? Cast<ABlasterHUD>(GetHUD()) : BlasterHUD;
	bool bHUDVALID = BlasterHUD && BlasterHUD->CharacterOverlay && 
		BlasterHUD->CharacterOverlay->HealthBar && 
		BlasterHUD->CharacterOverlay->HealthText;

	/*Logs to check if the hud is valid*/

//	if (BlasterHUD) UE_LOG(LogTemp, Warning, TEXT("BlasterHud Valid"));
//	if(BlasterHUD&&BlasterHUD->CharacterOverlay) UE_LOG(LogTemp, Warning, TEXT("BlasterHUD->CharacterOverlay Valid"));

	if (bHUDVALID) {
		const float HealthPercent = Health / MaxHealth;
		BlasterHUD->CharacterOverlay->HealthBar->SetPercent(HealthPercent);
		FString HealthText = FString::Printf(TEXT(" % d / % d"), FMath::CeilToInt(Health), FMath::CeilToInt(MaxHealth));
		BlasterHUD->CharacterOverlay->HealthText->SetText(FText::FromString(HealthText));
	}
}

void ABlasterPlayerController::SetHUDScore(float Score)
{
	BlasterHUD = BlasterHUD == nullptr ? Cast<ABlasterHUD>(GetHUD()) : BlasterHUD;
	bool bHUDVALID = BlasterHUD && BlasterHUD->CharacterOverlay &&
		BlasterHUD->CharacterOverlay->ScoreAmount;
	if (bHUDVALID) {
		FString ScoreText = FString::Printf(TEXT("%d"), FMath::FloorToInt(Score));
		BlasterHUD->CharacterOverlay->ScoreAmount->SetText(FText::FromString(ScoreText));
	}

}

void ABlasterPlayerController::SetHUDDefeats(int32 Defeats)
{
	BlasterHUD = BlasterHUD == nullptr ? Cast<ABlasterHUD>(GetHUD()) : BlasterHUD;
	bool bHUDVALID = BlasterHUD && BlasterHUD->CharacterOverlay &&
		BlasterHUD->CharacterOverlay->DefeatsAmount; 
	if (bHUDVALID) {
		FString DefeatsText = FString::Printf(TEXT("%d"), Defeats);
		BlasterHUD->CharacterOverlay->DefeatsAmount->SetText(FText::FromString(DefeatsText));
	}
}

void ABlasterPlayerController::SetHUDWeaponAmmo(int32 Ammo)
{
	BlasterHUD = BlasterHUD == nullptr ? Cast<ABlasterHUD>(GetHUD()) : BlasterHUD;
	bool bHUDVALID = BlasterHUD && BlasterHUD->CharacterOverlay &&
		BlasterHUD->CharacterOverlay->WeaponAmmoAmount;
	if (bHUDVALID) {
		FString AmmoText = FString::Printf(TEXT("%d"), Ammo);
		BlasterHUD->CharacterOverlay->WeaponAmmoAmount->SetText(FText::FromString(AmmoText));
	}
}

void ABlasterPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ABlasterCharacter* BlasterCharacter = Cast<ABlasterCharacter>(InPawn);
	if (BlasterCharacter) {
		SetHUDHealth(BlasterCharacter->GetHealth(), BlasterCharacter->GetMaxHealth());
	}
	HideDeathMessage();
}

void ABlasterPlayerController::UpdateDeathMessage(const FString KilledBy)
{
	BlasterHUD = BlasterHUD == nullptr ? Cast<ABlasterHUD>(GetHUD()) : BlasterHUD;
	if (BlasterHUD && BlasterHUD->CharacterOverlay &&
		BlasterHUD->CharacterOverlay->TxtDeathMessage &&
		BlasterHUD->CharacterOverlay->TxtKilledBy) {

		BlasterHUD->CharacterOverlay->TxtKilledBy->SetText(FText::FromString(KilledBy));
		BlasterHUD->CharacterOverlay->TxtKilledBy->SetVisibility(ESlateVisibility::Visible);
		BlasterHUD->CharacterOverlay->TxtDeathMessage->SetVisibility(ESlateVisibility::Visible);
	}
}

void ABlasterPlayerController::HideDeathMessage()
{
	BlasterHUD = BlasterHUD == nullptr ? Cast<ABlasterHUD>(GetHUD()) : BlasterHUD;
	if (BlasterHUD && BlasterHUD->CharacterOverlay &&
		BlasterHUD->CharacterOverlay->TxtDeathMessage &&
		BlasterHUD->CharacterOverlay->TxtKilledBy) {

		BlasterHUD->CharacterOverlay->TxtKilledBy->SetVisibility(ESlateVisibility::Collapsed);
		BlasterHUD->CharacterOverlay->TxtDeathMessage->SetVisibility(ESlateVisibility::Collapsed);
	}
}
