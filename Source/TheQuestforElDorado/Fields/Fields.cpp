#include "Fields.h"

AFields::AFields()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Attributes = CreateDefaultSubobject<UFieldAttributes>("Attributes");
	
	Field = CreateDefaultSubobject<UStaticMeshComponent>("Field");
	Field->SetVisibility(false);
	RootComponent = Field;

}

void AFields::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFields::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

