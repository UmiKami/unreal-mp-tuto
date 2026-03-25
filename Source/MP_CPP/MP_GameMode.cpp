// Fill out your copyright notice in the Description page of Project Settings.


#include "MP_GameMode.h"

#include "Game/MP_GameState.h"
#include "Utils/MP_MultiplayerUtils.h"

void AMP_GameMode::StartMatch()
{
	Super::StartMatch();
	
	UHelper::PrintToScreen(this, "Match has started!", FColor::Orange);
}

void AMP_GameMode::BeginPlay()
{
	Super::BeginPlay();
	
	
	GetWorldTimerManager().SetTimer(MatchStartDelay, this, &ThisClass::OnMatchStart, 4.f, false);
}

void AMP_GameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
	AMP_GameState* MPGameState = CastChecked<AMP_GameState>(GameState);

	TArray<APlayerController*> TeamOne = MPGameState->GetTeam(1);
	TArray<APlayerController*> TeamTwo = MPGameState->GetTeam(2);
	
	if (TeamOne.Num() >= TeamTwo.Num())
	{
		MPGameState->AddControllerToTeam(NewPlayer, 2);
	} else
	{
		MPGameState->AddControllerToTeam(NewPlayer, 1);
	}
	
}

void AMP_GameMode::OnMatchStart()
{
	StartMatch();
}
