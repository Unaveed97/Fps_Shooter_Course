// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_Fps_Shooter.h"
#include "FPS_Shooter/Character/BlasterCharacter.h"
#include "FPS_Shooter/PlayerController/BlasterPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"


void AGM_Fps_Shooter::PlayerEliminated(ABlasterCharacter* ElimanatedCharacter, ABlasterPlayerController* VictimController, ABlasterPlayerController* AttackerController)
{
	if (ElimanatedCharacter) {
		ElimanatedCharacter->Elim();
	}
}

void AGM_Fps_Shooter::RequestRespawn(ACharacter* ElimnedCharacter, AController* ElimnedController)
{	
	if (ElimnedCharacter) {
		ElimnedCharacter->Reset();
		ElimnedCharacter->Destroy();
	}
	if (ElimnedController) {
		TArray<AActor*> PlayerStarts;
		UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), PlayerStarts);

		TArray<AActor*>Characters;
		UGameplayStatics::GetAllActorsOfClass(this, ABlasterCharacter::StaticClass(), Characters);

		TArray<float>StockedDistances;

		for (int i = 0; i < PlayerStarts.Num(); i++)
		{
			float MinDistance = (PlayerStarts[i]->GetActorLocation() - Characters[0]->GetActorLocation()).Size();
			for (int j = 1; j < Characters.Num(); j++)
			{
				float Distance = (PlayerStarts[i]->GetActorLocation() - Characters[j]->GetActorLocation()).Size();
				if (Distance < MinDistance)
				{
					MinDistance = Distance;
				}
			}
			StockedDistances.Add(MinDistance);
		}

		float MaxDistance = StockedDistances[0];
		int32 Selection = 0;

		for (int i = 1; i < StockedDistances.Num(); i++)
		{
			if (MaxDistance < StockedDistances[i])
			{
				MaxDistance = StockedDistances[i];
				Selection = i;
			}
		}

		//int32 Selection = FMath::RandRange(0, PlayerStarts.Num() - 1);
		RestartPlayerAtPlayerStart(ElimnedController, PlayerStarts[Selection]);
	}
}
