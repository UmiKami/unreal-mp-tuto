// Fill out your copyright notice in the Description page of Project Settings.


#include "MP_HealthComponent.h"

#include "Net/UnrealNetwork.h"
#include "Utils/MP_MultiplayerUtils.h"


UMP_HealthComponent::UMP_HealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
}


void UMP_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UMP_HealthComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, Health);
}

void UMP_HealthComponent::AddHealth(float InAmount)
{
	Health += InAmount;
}

void UMP_HealthComponent::OnRep_Health()
{
	UMP_MultiplayerUtils::PrintToScreen(GetOwner(), FString::Printf(TEXT("Current Health: %.2f"), Health), FColor::Red);
}

