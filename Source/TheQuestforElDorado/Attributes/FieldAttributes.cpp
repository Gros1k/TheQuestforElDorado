#include "FieldAttributes.h"

UFieldAttributes::UFieldAttributes()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UFieldAttributes::BeginPlay()
{
	Super::BeginPlay();
}

void UFieldAttributes::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

