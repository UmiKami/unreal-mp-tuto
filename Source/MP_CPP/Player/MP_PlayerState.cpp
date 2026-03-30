// Fill out your copyright notice in the Description page of Project Settings.


#include "MP_PlayerState.h"

#include "Net/UnrealNetwork.h"
#include "Utils/MP_MultiplayerUtils.h"

AMP_PlayerState::AMP_PlayerState()
{
	SetNetUpdateFrequency(6);
}

void AMP_PlayerState::IncreasePickupCount()
{
	PickupCount++;
	
	if (HasAuthority())
	{
		// calls the function Server so it broadcasts signal on server
		OnRep_PickupCount();
	}
}

int32 AMP_PlayerState::GetPickupCount() const
{
	return PickupCount;
}

void AMP_PlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, PickupCount);
}

void AMP_PlayerState::OnRep_PickupCount()
{
	// UHelper::PrintToScreen(this, FString::Printf(TEXT("%s PlayerState Pickup Count: %d"), *GetName(), PickupCount), FColor::Turquoise);
	PickupCountSignature.Broadcast(PickupCount);
}

