// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BlasterPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class FPS_SHOOTER_API ABlasterPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
	virtual void OnRep_Score() override;
	
	UFUNCTION()
	virtual void OnRep_Defeats();

	UFUNCTION()
	void OnRep_KilledBy();

	void AddToScore(float ScoreAmount);
	void AddToDefeats(int32 DefeatsAmount);
	void UpdateDeathMessage(FString KillerName);

private:
	UPROPERTY()
	class ABlasterCharacter* Character;
	UPROPERTY()
	class ABlasterPlayerController* Controller;
	
	void UpdateDeathMessageHUD();

	UPROPERTY(ReplicatedUsing = OnRep_Defeats)
	int32 Defeats;

	UPROPERTY(ReplicatedUsing = OnRep_KilledBy)
	FString KilledBy;

	
};
