// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MP_HealthComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MP_CPP_API UMP_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMP_HealthComponent();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	void AddHealth(float InAmount);
	
	FORCEINLINE float GetHealth() const {return Health;}
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(ReplicatedUsing=OnRep_Health)
	float Health;
	
	UFUNCTION()
	void OnRep_Health();
};
