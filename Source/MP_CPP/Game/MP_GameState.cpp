// Fill out your copyright notice in the Description page of Project Settings.


#include "MP_GameState.h"

#include "Net/UnrealNetwork.h"


AMP_GameState::AMP_GameState()
{
}

void AMP_GameState::AddControllerToTeam(APlayerController* PC, int8 TeamNumber)
{
	if (!IsValid(PC)) return;

	switch (TeamNumber)
	{
	case 1:
		TeamOne.Add(PC);
		break;
	case 2:
		TeamTwo.Add(PC);
		break;
	default:
		break;
	}
}

TArray<APlayerController*> AMP_GameState::GetTeam(int8 TeamNumber)
{
	switch (TeamNumber)
	{
	case 1:
		return TeamOne;
	case 2:
		return TeamTwo;
	default:
		return {};
	}
}

TArray<APlayerController*> AMP_GameState::GetTeamByPlayController(APlayerController* PC)
{
	if (TeamOne.Contains(PC)) return TeamOne;
	if (TeamTwo.Contains(PC)) return TeamTwo;

	return {};
}

FString AMP_GameState::GetTeamNameByPlayController(APlayerController* PC) const
{
	if (TeamOne.Contains(PC)) return "Team 1";
	if (TeamTwo.Contains(PC)) return "Team 2";

	return "Not found.";
}

void AMP_GameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, TeamOne);
	DOREPLIFETIME(ThisClass, TeamTwo);
}
