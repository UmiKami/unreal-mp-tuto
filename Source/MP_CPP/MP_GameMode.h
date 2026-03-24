// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MP_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class MP_CPP_API AMP_GameMode : public AGameMode
{
	GENERATED_BODY()
protected:
	virtual void StartMatch() override;
	virtual void BeginPlay() override;
	
private:
	FTimerHandle MatchStartDelay;
	
	void OnMatchStart();
};
