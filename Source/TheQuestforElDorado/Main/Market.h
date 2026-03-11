#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Market.generated.h"

class ACards;

UCLASS()
class THEQUESTFORELDORADO_API AMarket : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:	
	AMarket();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Plate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* CameraPlace;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* One;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* Two;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* Three;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* Four;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* Five;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* Six;
	
	UPROPERTY(EditDefaultsOnly, Category = "SunCards")
	TSubclassOf<AActor> Fotoreporterka;
	UPROPERTY(EditDefaultsOnly, Category = "SunCards")
	TSubclassOf<AActor> Nadajnik;
	UPROPERTY(EditDefaultsOnly, Category = "SunCards")
	TSubclassOf<AActor> Odkrywca;
	UPROPERTY(EditDefaultsOnly, Category = "SunCards")
	TSubclassOf<AActor> Przewodnik;
	UPROPERTY(EditDefaultsOnly, Category = "SunCards")
	TSubclassOf<AActor> SkrzyniaSkarbow;
	UPROPERTY(EditDefaultsOnly, Category = "SunCards")
	TSubclassOf<AActor> Zwiadowca;
	
	UPROPERTY(EditDefaultsOnly, Category = "MarketCards")
	TSubclassOf<AActor> DRBotanik;
	UPROPERTY(EditDefaultsOnly, Category = "MarketCards")
	TSubclassOf<AActor> Dziennikarka;
	UPROPERTY(EditDefaultsOnly, Category = "MarketCards")
	TSubclassOf<AActor> DziennikPodrozy;
	UPROPERTY(EditDefaultsOnly, Category = "MarketCards")
	TSubclassOf<AActor> Hydroplan;
	UPROPERTY(EditDefaultsOnly, Category = "MarketCards")
	TSubclassOf<AActor> Kapitan;
	UPROPERTY(EditDefaultsOnly, Category = "MarketCards")
	TSubclassOf<AActor> Kartograf;
	UPROPERTY(EditDefaultsOnly, Category = "MarketCards")
	TSubclassOf<AActor> Kompas;
	UPROPERTY(EditDefaultsOnly, Category = "MarketCards")
	TSubclassOf<AActor> Milionerka;
	UPROPERTY(EditDefaultsOnly, Category = "MarketCards")
	TSubclassOf<AActor> Pionier;
	UPROPERTY(EditDefaultsOnly, Category = "MarketCards")
	TSubclassOf<AActor> Podrozniczka;
	UPROPERTY(EditDefaultsOnly, Category = "MarketCards")
	TSubclassOf<AActor> Tubylec;
	UPROPERTY(EditDefaultsOnly, Category = "MarketCards")
	TSubclassOf<AActor> WielkaMaczeta;

	
	UPROPERTY()
	TArray<ACards*> SunCards;
	UPROPERTY()
	TArray<ACards*> MarketCards;
	UPROPERTY()
	TArray<UBoxComponent*> Places;
};
