#include "MultiplayerState.h"
#include "Net/UnrealNetwork.h"

AMultiplayerState::AMultiplayerState()
{
	bReplicates = true;
}

void AMultiplayerState::CopyProperties(APlayerState* NewPlayerState)
{
	Super::CopyProperties(NewPlayerState);
	
	AMultiplayerState* PS = Cast<AMultiplayerState>(NewPlayerState);
	if (PS)
	{
		PS->PlayerColor = PlayerColor;
		PS->Expeditioner = Expeditioner;
		PS->Plate = Plate;
		PS->CardsStack = CardsStack;
		PS->CardsUsed = CardsUsed;
		PS->HandCards = HandCards;
		PS->SelectedCard = SelectedCard;
	}
}

void AMultiplayerState::OverrideWith(APlayerState* OldPlayerState)
{
	Super::OverrideWith(OldPlayerState);
	
	AMultiplayerState* PS = Cast<AMultiplayerState>(OldPlayerState);
	if (PS)
	{
		PlayerColor = PS->PlayerColor;
		Expeditioner = PS->Expeditioner;
		Plate = PS->Plate;
		CardsStack = PS->CardsStack;
		CardsUsed = PS->CardsUsed;
		HandCards = PS->HandCards;
		SelectedCard = PS->SelectedCard;
	}
}

void AMultiplayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AMultiplayerState, PlayerColor);
	DOREPLIFETIME(AMultiplayerState, Expeditioner);
	DOREPLIFETIME(AMultiplayerState, Plate);
	DOREPLIFETIME(AMultiplayerState, CardsStack);
	DOREPLIFETIME(AMultiplayerState, CardsUsed);
	DOREPLIFETIME(AMultiplayerState, HandCards);
	DOREPLIFETIME(AMultiplayerState, SelectedCard);
}
