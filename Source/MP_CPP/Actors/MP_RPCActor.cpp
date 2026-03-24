// Fill out your copyright notice in the Description page of Project Settings.


#include "MP_RPCActor.h"

#include "Utils/MP_MultiplayerUtils.h"


AMP_RPCActor::AMP_RPCActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>("DefaultSceneRoot");
	SetRootComponent(SceneRoot);
	
	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>("CubeMesh");
	CubeMesh->SetupAttachment(RootComponent);
	
	SetReplicates(true);
}

void AMP_RPCActor::BeginPlay()
{
	Super::BeginPlay();
	SetReplicateMovement(true);
	
	if (HasAuthority())
	{
		Client_PrintDebugMessage();
		Multicast_PrintMessage();
	}
}

void AMP_RPCActor::OnRep_Owner()
{
	Super::OnRep_Owner();
	
	Server_PrintMessage();
}

void AMP_RPCActor::Multicast_PrintMessage_Implementation()
{
	FString AuthorityMsg = HasAuthority() ? "Server: " : "Client: ";
	FString MsgString = FString::Printf(TEXT("%s Multicasst function called from Server!"), *AuthorityMsg);
	
	UMP_MultiplayerUtils::PrintToScreen(this, MsgString, FColor::Emerald);
}

/*
 * When object spawns on Server client, this function does not get called because we are already in the server and owning connection is None.
 * If the owner is assigned on Spawn, this function gets called on the clients up to the server.
 * If the owner is NOT assigned on Spawn, this function does not get called at all because owning connection is likely None.
 */
void AMP_RPCActor::Server_PrintMessage_Implementation()
{
	FString AuthorityMsg = HasAuthority() ? "Server: " : "Client: ";
	FString MsgString = FString::Printf(TEXT("%sObject %s spawned FROM SERVER RPC! "), *AuthorityMsg, *GetName());
	
	UMP_MultiplayerUtils::PrintToScreen(this, MsgString, FColor::FromHex("#c421ff"));
}

void AMP_RPCActor::Client_PrintDebugMessage_Implementation()
{
	FString AuthorityMsg = HasAuthority() ? "Server: " : "Client: ";
	FString MsgString = FString::Printf(TEXT("%sObject %s spawned!"), *AuthorityMsg, *GetName());
	
	UMP_MultiplayerUtils::PrintToScreen(this, MsgString, FColor::MakeRandomColor());
	
}

