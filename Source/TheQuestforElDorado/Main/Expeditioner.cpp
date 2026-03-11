#include "Expeditioner.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../Includes/Define.h"

AExpeditioner::AExpeditioner()
{
	PrimaryActorTick.bCanEverTick = true;
	
	bReplicates = true;
	
	Expeditioner = CreateDefaultSubobject<UStaticMeshComponent>("Expeditioner");
	Expeditioner->SetupAttachment(RootComponent);
	
	CameraPlace = CreateDefaultSubobject<USceneComponent>("CameraPlace");	//karty w ręce
	CameraPlace->SetupAttachment(Expeditioner);
}

void AExpeditioner::BeginPlay()
{
	Super::BeginPlay();
	
}

void AExpeditioner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AExpeditioner::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AExpeditioner::MoveToField(AActor* Observer)
{
	AActor* ObservedActor = LookInterface->Look(Observer);
	if (ObservedActor)
	{
		if (ObservedActor->GetName().Contains(TEXT("Field")))
	    {
	        ServerMoveActor
	        (
        		FVector
        		(
        			ObservedActor->GetActorLocation().X,
        			ObservedActor->GetActorLocation().Y,
        			GetActorLocation().Z
        		)	
	        );
	    }
	}

}

void AExpeditioner::ServerMoveActor_Implementation(FVector NewLocation)
{
    SetActorLocation(NewLocation);
}