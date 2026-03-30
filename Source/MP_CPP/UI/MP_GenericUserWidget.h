// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MP_GenericUserWidget.generated.h"

class AMP_PlayerState;
/**
 * 
 */
UCLASS()
class MP_CPP_API UMP_GenericUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<AMP_PlayerState> MPPlayerState;
};
