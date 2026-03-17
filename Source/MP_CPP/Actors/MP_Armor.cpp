// Fill out your copyright notice in the Description page of Project Settings.


#include "MP_Armor.h"

#include "Components/SphereComponent.h"
#include "Interaction/MP_Player.h"


AMP_Armor::AMP_Armor()
{
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));

	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>("SphereMesh");
	SphereMesh->SetupAttachment(RootComponent);
	SphereMesh->SetIsReplicated(true);

	CapsuleMesh = CreateDefaultSubobject<UStaticMeshComponent>("CapsuleMesh");
	CapsuleMesh->SetupAttachment(RootComponent);
	CapsuleMesh->SetIsReplicated(true);

	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SphereCollision->SetupAttachment(RootComponent);
}

void AMP_Armor::BeginPlay()
{
	Super::BeginPlay();
}

void AMP_Armor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMP_Armor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (!HasAuthority()) return;
	
	if (OtherActor->Implements<UMP_Player>())
	{
		USkeletalMeshComponent* Mesh = IMP_Player::Execute_GetSkeletalMesh(OtherActor);
		
		SphereMesh->AttachToComponent(Mesh,
									  FAttachmentTransformRules::SnapToTargetNotIncludingScale, "S_Head");
		CapsuleMesh->AttachToComponent(Mesh,
									   FAttachmentTransformRules::SnapToTargetNotIncludingScale, "S_Chest");
		
		IMP_Player::Execute_GrantArmor(OtherActor, ArmorValue);
	}
}
