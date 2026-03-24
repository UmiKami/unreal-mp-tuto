// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MP_RPCActor.generated.h"

UCLASS()
class MP_CPP_API AMP_RPCActor : public AActor
{
	GENERATED_BODY()

public:
	AMP_RPCActor();

protected:
	virtual void BeginPlay() override;
	virtual void OnRep_Owner() override;

private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> CubeMesh;
	
	UFUNCTION(Client, Reliable)
	void Client_PrintDebugMessage();
	
	UFUNCTION(Server, Reliable)
	void Server_PrintMessage();
	
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_PrintMessage();
	
};
