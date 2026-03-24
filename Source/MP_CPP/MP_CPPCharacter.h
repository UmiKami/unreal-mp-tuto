// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interaction/MP_Player.h"
#include "Logging/LogMacros.h"
#include "MP_CPPCharacter.generated.h"

class AMP_RPCActor;
class UMP_HealthComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  A simple player-controllable third person character
 *  Implements a controllable orbiting camera
 */
UCLASS(abstract)
class AMP_CPPCharacter : public ACharacter, public IMP_Player
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
protected:

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MouseLookAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* PrintArmorAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* SpawnObjectAction;
public:

	/** Constructor */
	AMP_CPPCharacter();	
	
	void AddBonusSpeed(float BonusSpeed) const;
	
	// start IMP_Player Interface
	virtual USkeletalMeshComponent* GetSkeletalMesh_Implementation() const override;	
	virtual void GrantArmor_Implementation(float ArmorAmount) override;
	// end IMP_Player Interface
protected:

	/** Initialize input action bindings */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	
	void GeneralInput(const FInputActionValue& Value);

public:

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles look inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoLook(float Yaw, float Pitch);

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
#pragma region Crash Course
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker) override;
	virtual void AddToPickupCount_Implementation() override;
	
private:
	UPROPERTY(ReplicatedUsing=OnRep_Armor)
	float Armor;
	
	UFUNCTION()
	void OnRep_Armor();
	
	UPROPERTY(ReplicatedUsing=OnRep_PickupCount)
	int32 PickupCount = 0;
	
	UFUNCTION()
	void OnRep_PickupCount(int32 PreviousCount);
	
	bool bReplicatePickupCount = false;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UMP_HealthComponent> HealthComponent;
	
	/* Remote Procedure Call (RPC) - Client, Server, and NetMulticast */
	
	UFUNCTION(Client, Reliable)
	void Client_PrintMessage(const FString& Message);
	
	FTimerHandle RPCDelayTimer;
	
	void OnRPCDelayTimer();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMP_RPCActor> SpawnObjectClass;
	
	UFUNCTION(Server, Reliable)
	void DoSpawnObject();
	
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_PrintMessage(const FString& Message);
	
	
protected:
	virtual void BeginPlay() override;
	
#pragma endregion
	
};

