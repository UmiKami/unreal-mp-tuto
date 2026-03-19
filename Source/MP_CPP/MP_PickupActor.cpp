// Fill out your copyright notice in the Description page of Project Settings.


#include "MP_PickupActor.h"

#include "Components/SphereComponent.h"
#include "Interaction/MP_Player.h"


// Sets default values
AMP_PickupActor::AMP_PickupActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollider");
	SetRootComponent(SphereCollision);
	
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>("SphereMesh");
	SphereMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMP_PickupActor::BeginPlay()
{
	Super::BeginPlay();
	
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnSphereComponentBeginOverlap);
}

void AMP_PickupActor::OnSphereComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!HasAuthority()) return;
	
	if (OtherActor->Implements<UMP_Player>())
	{
		IMP_Player::Execute_AddToPickupCount(OtherActor);
		Destroy();
	}
}
