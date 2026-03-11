#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "TheQuestforElDorado/Includes/GameTypes.h"
#include "TheQuestforElDorado/Interfaces/LookInterface.h"
#include "ExpeditionPlate.generated.h"

class AMarket;
class APlayers;
class ACards;

UCLASS()
class THEQUESTFORELDORADO_API AExpeditionPlate : public AActor
{
	GENERATED_BODY()
	
	ILookInterface* LookInterface;
	
protected:
	virtual void BeginPlay() override;

public:	
	AExpeditionPlate();
	virtual void Tick(float DeltaTime) override;

	void CreateCards(APlayers* Player);

	void TakeCards();
	void ChooseCards(AActor* Observer);
	void EndTurn(APlayers* Player);
	void TakeCardsToHand(int Count, bool NewCards);
	void TakeSunCards(AActor* ChooseActor);
	
	UFUNCTION(Server, Reliable)
	void ServerSpawnCard(TSubclassOf<AActor> Card);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Plate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    UBoxComponent* Stack;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    UBoxComponent* Used;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* Hand;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* CameraPlace;
	
	UPROPERTY(EditDefaultsOnly, Category = "BasicCards")
	TSubclassOf<AActor> Globtroter;
	UPROPERTY(EditDefaultsOnly, Category = "BasicCards")
	TSubclassOf<AActor> Marynarz;
	UPROPERTY(EditDefaultsOnly, Category = "BasicCards")
	TSubclassOf<AActor> Turystka;

	UPROPERTY()
	APlayers* OwningPlayer;

	UPROPERTY()
	AMarket* Market;
	
	ECardsState CardsState = ECardsState::Empty;
	
	bool IsLowStack = false;

	static TArray<UBoxComponent*> EmptyPlaces;
	
	int CountCardsToGetOutOfMyFuckingWayYouFuckingPeaceOfWood = 0;
};
