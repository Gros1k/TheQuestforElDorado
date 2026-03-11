#include "Market.h"
#include "Cards.h"
#include "GameFramework/GameModeBase.h"
#include "Net/UnrealNetwork.h"
#include "TheQuestforElDorado/Includes/Define.h"

AMarket::AMarket()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	Plate = CreateDefaultSubobject<UStaticMeshComponent>("Plate");
	
	CameraPlace = CreateDefaultSubobject<USceneComponent>("CameraPlace");
	CameraPlace->SetupAttachment(Plate);
	
	One = CreateDefaultSubobject<UBoxComponent>("One");
	One->SetupAttachment(Plate);
	
	Two = CreateDefaultSubobject<UBoxComponent>("Two");
	Two->SetupAttachment(Plate);
	
	Three = CreateDefaultSubobject<UBoxComponent>("Three");
	Three->SetupAttachment(Plate);
	
	Four = CreateDefaultSubobject<UBoxComponent>("Four");
	Four->SetupAttachment(Plate);
	
	Five = CreateDefaultSubobject<UBoxComponent>("Five");
	Five->SetupAttachment(Plate);
	
	Six = CreateDefaultSubobject<UBoxComponent>("Six");
	Six->SetupAttachment(Plate);
}

void AMarket::BeginPlay()
{
	Super::BeginPlay();
	
	Places.Add(One);
	Places.Add(Two);
	Places.Add(Three);
	Places.Add(Four);
	Places.Add(Five);
	Places.Add(Six);
	
	if (HasAuthority())
	{
		for (int i = 0; i <= 2; i++){SunCards.Add(GetWorld()->SpawnActor<ACards>(Fotoreporterka));}
        for (int i = 0; i <= 2; i++){SunCards.Add(GetWorld()->SpawnActor<ACards>(Nadajnik));}
        for (int i = 0; i <= 2; i++){SunCards.Add(GetWorld()->SpawnActor<ACards>(Odkrywca));}
        for (int i = 0; i <= 2; i++){SunCards.Add(GetWorld()->SpawnActor<ACards>(Przewodnik));}
        for (int i = 0; i <= 2; i++){SunCards.Add(GetWorld()->SpawnActor<ACards>(SkrzyniaSkarbow));}
        for (int i = 0; i <= 2; i++){SunCards.Add(GetWorld()->SpawnActor<ACards>(Zwiadowca));}
        	
        for (int i = 0; i <= 2; i++){MarketCards.Add(GetWorld()->SpawnActor<ACards>(DRBotanik));}
        for (int i = 0; i <= 2; i++){MarketCards.Add(GetWorld()->SpawnActor<ACards>(Dziennikarka));}
        for (int i = 0; i <= 2; i++){MarketCards.Add(GetWorld()->SpawnActor<ACards>(DziennikPodrozy));}
        for (int i = 0; i <= 2; i++){MarketCards.Add(GetWorld()->SpawnActor<ACards>(Hydroplan));}
        for (int i = 0; i <= 2; i++){MarketCards.Add(GetWorld()->SpawnActor<ACards>(Kartograf));}
        for (int i = 0; i <= 2; i++){MarketCards.Add(GetWorld()->SpawnActor<ACards>(Kapitan));}
        
        for (int i = 0; i <= 2; i++){MarketCards.Add(GetWorld()->SpawnActor<ACards>(Kompas));}
        for (int i = 0; i <= 2; i++){MarketCards.Add(GetWorld()->SpawnActor<ACards>(Milionerka));}
        for (int i = 0; i <= 2; i++){MarketCards.Add(GetWorld()->SpawnActor<ACards>(Pionier));}
        for (int i = 0; i <= 2; i++){MarketCards.Add(GetWorld()->SpawnActor<ACards>(Podrozniczka));}
        for (int i = 0; i <= 2; i++){MarketCards.Add(GetWorld()->SpawnActor<ACards>(WielkaMaczeta));}
        for (int i = 0; i <= 2; i++){MarketCards.Add(GetWorld()->SpawnActor<ACards>(Tubylec));}
	}
	
	for (int i = 0, x = 0; i < SunCards.Num() - 1; i+=3)
	{
		SunCards[i]->SetActorLocation(Places[x]->GetComponentLocation());
		SunCards[i + 1]->SetActorLocation(Places[x]->GetComponentLocation());
		SunCards[i + 2]->SetActorLocation(Places[x]->GetComponentLocation());	
		x++;
	}
	
	for (int i = 0, x = 0, a = 150.f; i < MarketCards.Num() - 2; i+=3)
	{
		MarketCards[i]->SetActorLocation(Places[x]->GetComponentLocation() - FVector(0.f,a, 0.f));
		MarketCards[i + 1]->SetActorLocation(Places[x]->GetComponentLocation() - FVector(0.f,a, 0.f));
		MarketCards[i + 2]->SetActorLocation(Places[x]->GetComponentLocation() - FVector(0.f,a, 0.f));
		x++;
		if (x == 6)
		{
			a = 300.f;
			x = 0;
		}
	}
	
}

void AMarket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

