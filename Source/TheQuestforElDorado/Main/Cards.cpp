#include "Cards.h"

ACards::ACards()
{
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;
}

void ACards::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACards::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACards::ServerMoveActor_Implementation(FVector NewLocation)
{
	SetActorLocation(NewLocation);
}

void ACards::ServerRotateActor_Implementation(FRotator NewRotation)
{
	SetActorRotation(NewRotation);
}