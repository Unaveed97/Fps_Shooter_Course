// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponState : uint8 {
	EWS_Initial UMETA(DisplayName = "Initial State"),
	EWS_Equipped UMETA(DisplayName = "Equipped"),
	EWS_Dropped UMETA(DisplayName = "Dropped"),


	EWS_MAX UMETA(DisplayName = "DefaultMAX")
};

UCLASS()
class FPS_SHOOTER_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void ShowPickupWeapon(bool bShowWidget);
	virtual void Fire(const FVector& HitTarget);

	// Textures for weapon crosshair
	UPROPERTY(EditAnywhere, Category = "CrossHair")
	class UTexture2D* CrosshairsCenter;

	UPROPERTY(EditAnywhere, Category = "CrossHair")
	class UTexture2D* CrosshairsLeft;

	UPROPERTY(EditAnywhere, Category = "CrossHair")
	class UTexture2D* CrosshairsRight;

	UPROPERTY(EditAnywhere, Category = "CrossHair")
	class UTexture2D* CrosshairsTop;

	UPROPERTY(EditAnywhere, Category = "CrossHair")
	class UTexture2D* CrosshairsBottom;

	// Zoomed FOV While Aiming

	UPROPERTY(EditAnywhere)
	float ZoomedFOV = 30.f;

	UPROPERTY(EditAnywhere)
	float ZoomInterpSpeed = 20.f;

	/*
	* Automatic fire 
	*/

	UPROPERTY(EditAnywhere, Category = "Combat")
		float FireDelay = .15f;

	UPROPERTY(EditAnywhere, Category = "Combat")
		bool bAutomatic = true;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnSphereOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION()
	void OnSphereEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	); 

private:
	UPROPERTY(VisibleAnywhere, Category = "Weapon Property")
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(VisibleAnywhere, Category = "Weapon Property")
	class USphereComponent* AreaSphere;

	UPROPERTY(ReplicatedUsing = OnRep_WeaponState, VisibleAnywhere, Category = "Weapon Property")
	EWeaponState WeaponState;

	UFUNCTION()
	void OnRep_WeaponState();

	UPROPERTY(VisibleAnywhere, Category = "Weapon Property")
	class UWidgetComponent* PickUpWidget;

	UPROPERTY(EditAnywhere, Category = "Weapon Property")
	class UAnimationAsset* FireAnimation;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ACasing> CasingClass;

public:	
	void SetWeaponState(EWeaponState State);
	FORCEINLINE USphereComponent* GetAreaSphere() const { return AreaSphere; }
	FORCEINLINE USkeletalMeshComponent* GetWeaponMesh() const { return SkeletalMesh; }
	FORCEINLINE float GetZoomedFOV() const { return ZoomedFOV; }
	FORCEINLINE float GetZoomInterpSpeed() const { return ZoomInterpSpeed; }
};
