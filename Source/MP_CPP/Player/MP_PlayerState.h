// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MP_PlayerState.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerStateUpdateSignature, int32, PickupCount);

/**
 * 
 */
UCLASS()
class MP_CPP_API AMP_PlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	AMP_PlayerState();
	
	void IncreasePickupCount();
	
	int32 GetPickupCount() const;
	
	UPROPERTY(BlueprintAssignable)
	FPlayerStateUpdateSignature PickupCountSignature;
	
protected:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
private:
	UPROPERTY(ReplicatedUsing=OnRep_PickupCount)
	int32 PickupCount;
	
	UFUNCTION()
	void OnRep_PickupCount();
};
