#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cards.generated.h"

UCLASS()
class THEQUESTFORELDORADO_API ACards : public AActor
{
	GENERATED_BODY()
	
public:	
	ACards();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "Attribiutes")
	bool bToBox = false;
	UPROPERTY(EditDefaultsOnly, Category = "Attribiutes")
	bool bAnyCardsFromMarket = false;
	UPROPERTY(EditDefaultsOnly, Category = "Attribiutes")
	int CountCardsToTake = 0;
	UPROPERTY(EditDefaultsOnly, Category = "Attribiutes")
	int CountCardsToGetOutOfMyFuckingWayYouFuckingPeaceOfWood = 0;
	
	UFUNCTION(Server, Reliable)
	void ServerMoveActor(FVector NewLocation);
	UFUNCTION(Server, Reliable)
	void ServerRotateActor(FRotator NewRotation);
};
