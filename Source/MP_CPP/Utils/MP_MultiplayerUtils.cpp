// Fill out your copyright notice in the Description page of Project Settings.


#include "MP_MultiplayerUtils.h"

void UMP_MultiplayerUtils::PrintLocalNetRole(AActor* Actor)
{
	if (Actor->HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] has authority."), *Actor->GetName())
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] does not have authority."), *Actor->GetName())
	}

	switch (Actor->GetLocalRole())
	{
		case ROLE_None:
			UE_LOG(LogTemp, Warning, TEXT("Actor [%s] has No role."), *Actor->GetName())
			break;
		case ROLE_SimulatedProxy:
			UE_LOG(LogTemp, Warning, TEXT("Actor [%s] has Simulated Proxy Role."), *Actor->GetName())
			break;
		case ROLE_AutonomousProxy:
			UE_LOG(LogTemp, Warning, TEXT("Actor [%s] has Autonomous Proxy Role."), *Actor->GetName())
			break;
		case ROLE_Authority:
			UE_LOG(LogTemp, Warning, TEXT("Actor [%s] has Authority Role."), *Actor->GetName())
			break;
		case ROLE_MAX:
			UE_LOG(LogTemp, Warning, TEXT("Actor [%s] has Max Role."), *Actor->GetName())
			break;
	}
}

void UMP_MultiplayerUtils::PrintRemoteNetRole(AActor* Actor)
{
	if (Actor->HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] has authority on REMOTE."), *Actor->GetName())
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] does not have authority on REMOTE."), *Actor->GetName())
	}

	switch (Actor->GetRemoteRole())
	{
	case ROLE_None:
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] has No role on remote."), *Actor->GetName())
		break;
	case ROLE_SimulatedProxy:
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] has Simulated Proxy Role on remote."), *Actor->GetName())
		break;
	case ROLE_AutonomousProxy:
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] has Autonomous Proxy Role on remote."), *Actor->GetName())
		break;
	case ROLE_Authority:
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] has Authority Role on remote."), *Actor->GetName())
		break;
	case ROLE_MAX:
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] has Max Role on remote."), *Actor->GetName())
		break;
	}
}
