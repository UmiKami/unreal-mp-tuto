// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MP_GameState.generated.h"

/**
 * 
 */
UCLASS()
class MP_CPP_API AMP_GameState : public AGameState
{
	GENERATED_BODY()
	
public:
	AMP_GameState();

	void AddControllerToTeam(APlayerController* PC, int8 TeamNumber);
	
	TArray<APlayerController*> GetTeam(int8 TeamNumber);
	TArray<APlayerController*> GetTeamByPlayController(APlayerController* PC);
	FString GetTeamNameByPlayController(APlayerController* PC) const;
protected:
	// NOTE: GetLifetimeReplicatedProps method is REQUIRED when you have ANY replicated members of a class.
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
private:
	UPROPERTY(VisibleAnywhere, Replicated)
	TArray<APlayerController*> TeamOne = {};
	
	UPROPERTY(VisibleAnywhere, Replicated)
	TArray<APlayerController*> TeamTwo = {};
};
