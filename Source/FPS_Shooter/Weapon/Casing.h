// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Casing.generated.h"

UCLASS()
class FPS_SHOOTER_API ACasing : public AActor
{
	GENERATED_BODY()
	
public:	
	ACasing();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


private:
		UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* CasingMesh;

		UPROPERTY(EditAnywhere)
		float ShellEjectImpulseMin;

		UPROPERTY(EditAnywhere)
		float ShellEjectImpulseMax;

		UPROPERTY(EditAnywhere)
		class USoundCue* ShellSound;

		void DestroyShell();

public:	

};
