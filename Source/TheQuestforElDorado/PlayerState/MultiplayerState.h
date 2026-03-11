#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MultiplayerState.generated.h"

class ACards;
class AExpeditionPlate;
class AExpeditioner;

UCLASS()
class THEQUESTFORELDORADO_API AMultiplayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	
	AMultiplayerState();
	
	UPROPERTY(Replicated)
	FString PlayerColor;
	
	UPROPERTY(Replicated)
	AExpeditioner* Expeditioner;
	
	UPROPERTY(Replicated)
	AExpeditionPlate* Plate;
	
	UPROPERTY(Replicated)
	TArray<ACards*> CardsStack;
	UPROPERTY(Replicated)
	TArray<ACards*> CardsUsed;
	UPROPERTY(Replicated)
	TArray<ACards*> HandCards;
	UPROPERTY(Replicated)
	ACards* SelectedCard;
	
	virtual void CopyProperties(APlayerState* NewPlayerState) override;
	virtual void OverrideWith(APlayerState* OldPlayerState) override;
protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
