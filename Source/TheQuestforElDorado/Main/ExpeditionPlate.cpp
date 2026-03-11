#include "ExpeditionPlate.h"
#include "Cards.h"
#include "EngineUtils.h"
#include "Market.h"
#include "Players.h"
#include "Microsoft/AllowMicrosoftPlatformTypes.h"
#include "Runtime/Core/Tests/Containers/TestUtils.h"
#include "TheQuestforElDorado/Includes/Define.h"
#include "GameFramework/GameModeBase.h"
#include "Net/UnrealNetwork.h"
#include "TheQuestforElDorado/PlayerState/MultiplayerState.h"

TArray<UBoxComponent*> AExpeditionPlate::EmptyPlaces;

AExpeditionPlate::AExpeditionPlate()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	
	Plate = CreateDefaultSubobject<UStaticMeshComponent>("Plate");	//mesh
	
	Stack = CreateDefaultSubobject<UBoxComponent>("Stack");	//stos kart
	Stack->SetupAttachment(Plate);
	
	Used = CreateDefaultSubobject<UBoxComponent>("Used");	//stos kart użytych
	Used->SetupAttachment(Plate);
	
	Hand = CreateDefaultSubobject<USceneComponent>("Hand");	//karty w ręce
	Hand->SetupAttachment(Plate);
	
	CameraPlace = CreateDefaultSubobject<USceneComponent>("CameraPlace");	//karty w ręce
	CameraPlace->SetupAttachment(Plate);
}

void AExpeditionPlate::BeginPlay()
{
	Super::BeginPlay();
	
	for (TActorIterator<AMarket> It(GetWorld()); It; ++It)
	{
		Market = *It;
		break;
	}
	
}

void AExpeditionPlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AExpeditionPlate::CreateCards(APlayers* Player)
{
	OwningPlayer = Player;

	// tworzenie podstawowych kart, dodanie ich do stosu kart i przesunięcie na stos kart
	for (int i = 0; i <= 2; i++)
	{
		ServerSpawnCard(Globtroter);
		TOSTACK(OwningPlayer->GetPlayerState<AMultiplayerState>()->CardsStack[i])
	}

	for (int i = 3; i <= 6; i++)
	{
		ServerSpawnCard(Turystka);
		TOSTACK(OwningPlayer->GetPlayerState<AMultiplayerState>()->CardsStack[i])
	}

	ServerSpawnCard(Marynarz);
	TOSTACK(OwningPlayer->GetPlayerState<AMultiplayerState>()->CardsStack[7])
    
	// //przetasowanie kart
	Test::Shuffle(OwningPlayer->GetPlayerState<AMultiplayerState>()->CardsStack);
 
	// wzięcie kart
	TakeCards();
}

void AExpeditionPlate::TakeCards()
{
	if (CardsState == ECardsState::Empty)	//Jeśli nie ma żadnej karty w ręku
	{
		TakeCardsToHand(4, true);	//bierze do ręki 4 karty jako nowe
	}
	else if (CardsState == ECardsState::Incomplete)	//jeśli nie ma wszystkich ( < 4) kart w ręku
	{
		TakeCardsToHand(4 - OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards.Num(), true);	//bierze do ręki do 4 kart jako nowe
		
		if (OwningPlayer->GetPlayerState<AMultiplayerState>()->SelectedCard)	//Jeśli jest wybrana jakaś karta
		{
			TakeCardsToHand(OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards.Num() - 1, false);	//dołącz karty do ręki aby po usunięciu była na odpowiednich miejscach

			for (int i = 0; i <= OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards.Num() - 1; i++)
			{
				OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards[i]->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);	//odłącza wszystkie karty 
			}
			CARDUP(OwningPlayer->GetPlayerState<AMultiplayerState>()->SelectedCard)	//bierze do góry wybraną kartę 
		}
	}
	CardsState = ECardsState::Full;	//ustawia stan kart jako pełny
}

void AExpeditionPlate::ChooseCards(AActor* Observer)	//jeśli klikniesz na kartę
{
	if (AActor* ChooseActor = LookInterface->Look(Observer))	//jeśli patrzymy na jakiegoś aktora
	{
		if (ChooseActor == this)	//jeśli klikniesz na płytkę ekspedycji
		{
			if (OwningPlayer->GetPlayerState<AMultiplayerState>()->SelectedCard)	//jeśli jest wybrana jakaś karta
			{
				if (OwningPlayer->GetPlayerState<AMultiplayerState>()->SelectedCard->bToBox)	//Jeśli karta ma trafić do pudełka
				{
					OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards.Remove(OwningPlayer->GetPlayerState<AMultiplayerState>()->SelectedCard);	//usuń kartę z kart z ręki
					GetWorld()->GetAuthGameMode()->GetWorld()->DestroyActor(OwningPlayer->GetPlayerState<AMultiplayerState>()->SelectedCard);	//usuwa aktora
				}
				if (OwningPlayer->GetPlayerState<AMultiplayerState>()->SelectedCard->CountCardsToTake > 0)	//Jeśli karta umożliwia dobranie kart
				{
					TakeCardsToHand(OwningPlayer->GetPlayerState<AMultiplayerState>()->SelectedCard->CountCardsToTake, true);	//dobiera karty jako nowe
				}
				if (OwningPlayer->GetPlayerState<AMultiplayerState>()->SelectedCard->CountCardsToGetOutOfMyFuckingWayYouFuckingPeaceOfWood > 0)	//Jeśli karta umożliwia
				{
					CountCardsToGetOutOfMyFuckingWayYouFuckingPeaceOfWood += OwningPlayer->GetPlayerState<AMultiplayerState>()->SelectedCard->CountCardsToGetOutOfMyFuckingWayYouFuckingPeaceOfWood;
				}
				if (!OwningPlayer->GetPlayerState<AMultiplayerState>()->SelectedCard->bToBox)
				{
					OwningPlayer->GetPlayerState<AMultiplayerState>()->CardsUsed.Add(OwningPlayer->GetPlayerState<AMultiplayerState>()->SelectedCard);
                    OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards.Remove(OwningPlayer->GetPlayerState<AMultiplayerState>()->SelectedCard);
                    TOUSED(OwningPlayer->GetPlayerState<AMultiplayerState>()->SelectedCard)
                    TOUSED(OwningPlayer->GetPlayerState<AMultiplayerState>()->CardsUsed.Last())
					OwningPlayer->GetPlayerState<AMultiplayerState>()->SelectedCard = nullptr;	
				}
				
				if (!OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards.IsEmpty())
				{
					TakeCardsToHand(OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards.Num() - 1, false);
				}
			}
		}
		else if (OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards.Contains(ChooseActor))	//jeżeli kliknięta karta jest w ręku
        {
			for (int i = 0; i <= OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards.Num() - 1; i++)
            {
                OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards[i]->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
            }
			
			if (CountCardsToGetOutOfMyFuckingWayYouFuckingPeaceOfWood > 0 and GetKeyState(VK_SHIFT) < 0)
            {
            	CountCardsToGetOutOfMyFuckingWayYouFuckingPeaceOfWood--;
				if (Cast<ACards>(ChooseActor))
				{
					OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards.Remove(Cast<ACards>(ChooseActor));
				}
            	GetWorld()->GetAuthGameMode()->GetWorld()->DestroyActor(ChooseActor);
				TakeCardsToHand(OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards.Num() - 1, false);
            }
			
			if (OwningPlayer->GetPlayerState<AMultiplayerState>()->SelectedCard == nullptr)
			{
				OwningPlayer->GetPlayerState<AMultiplayerState>()->SelectedCard = Cast<ACards>(ChooseActor);
				CARDUP(OwningPlayer->GetPlayerState<AMultiplayerState>()->SelectedCard)
			}
			else if (ChooseActor != OwningPlayer->GetPlayerState<AMultiplayerState>()->SelectedCard)
			{
                if (OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards.Contains(OwningPlayer->GetPlayerState<AMultiplayerState>()->SelectedCard))
                {
                	CARDDOWN(OwningPlayer->GetPlayerState<AMultiplayerState>()->SelectedCard)
                }
                OwningPlayer->GetPlayerState<AMultiplayerState>()->SelectedCard = Cast<ACards>(ChooseActor);
                CARDUP(OwningPlayer->GetPlayerState<AMultiplayerState>()->SelectedCard)
			}

		}
		else if (OwningPlayer->GetPlayerState<AMultiplayerState>()->SelectedCard)
		{
			if (OwningPlayer->GetPlayerState<AMultiplayerState>()->SelectedCard->bAnyCardsFromMarket)
			{
				if (Market->SunCards.Contains(ChooseActor) or Market->MarketCards.Contains(ChooseActor))
				{
					TakeSunCards(ChooseActor);
					OwningPlayer->GetPlayerState<AMultiplayerState>()->SelectedCard = nullptr;
				}
			}
		}
		else if (Market->SunCards.Contains(ChooseActor))	//jeśli wybraną kartę można kupić
		{
			TakeSunCards(ChooseActor);
		}
		else if (Market->MarketCards.Contains(ChooseActor))	//jeśli wybrana karta jest niedostępna
        {
         	if (!EmptyPlaces.IsEmpty())	//jeśli jest jakieś miejsce wolne
         	{
         		for (int i = 0; i < Market->MarketCards.Num(); i++)
         		{
         			if (Market->MarketCards[i]->GetName().Contains(ChooseActor->GetName().Mid(3, ChooseActor->GetName().Len() - 7)))
         			{
         				Market->MarketCards[i]->ServerMoveActor(EmptyPlaces[0]->GetComponentLocation());
						Market->SunCards.Add(Market->MarketCards[i]);
         			}
         		}
	            for (int i = 0; i < Market->SunCards.Num(); ++i)
	            {
	            	if (Market->MarketCards.Contains(Market->SunCards[i]))
	            	{
	            		Market->MarketCards.Remove(Market->SunCards[i]);
	            	}
	            }
         		if (Cast<ACards>(ChooseActor))
         		{
         			OwningPlayer->GetPlayerState<AMultiplayerState>()->CardsUsed.Add(Cast<ACards>(ChooseActor));
                    TOUSED(Cast<ACards>(ChooseActor))
                    Market->SunCards.Remove(Cast<ACards>(ChooseActor));
         		}
	     		EmptyPlaces.RemoveAt(0);
         	}
        }
	}
}

void AExpeditionPlate::EndTurn(APlayers* Player)
{
	// if (Players.Find(Player) == 3)
	// {
	// 	GetWorld()->GetFirstPlayerController()->Possess(Players[0]);
	// }
	// else
	// {
	// 	GetWorld()->GetFirstPlayerController()->Possess(Players[Players.Find(Player) + 1]);
	// }
	if (OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards.Num() < 4)
	{
		CardsState = ECardsState::Incomplete;
		if (OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards.Num() == 0)
		{
			CardsState = ECardsState::Empty;
		}
		
		if (OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards.Num() + Cast<APlayers>(OwningPlayer)->GetPlayerState<AMultiplayerState>()->CardsStack.Num() < 4)
		{
			IsLowStack = true;
		}
	}
	else
	{
		CardsState = ECardsState::Full;
	}
	TakeCards();
}

void AExpeditionPlate::TakeCardsToHand(int Count, bool NewCards)
{
	if (Count < 0)
	{
		return;
	}
	
	if (IsLowStack or Count > Cast<APlayers>(OwningPlayer)->GetPlayerState<AMultiplayerState>()->CardsStack.Num() and NewCards)	//jeśli musi uzupełnić stos kart kartami użytymi
	{
		IsLowStack = false;
		
		Test::Shuffle(OwningPlayer->GetPlayerState<AMultiplayerState>()->CardsUsed);
		
		for (int i = 0, X = OwningPlayer->GetPlayerState<AMultiplayerState>()->CardsUsed.Num(); i <= X - 1; i++)
		{
			TOSTACK(OwningPlayer->GetPlayerState<AMultiplayerState>()->CardsUsed[0])
			
			Cast<APlayers>(OwningPlayer)->GetPlayerState<AMultiplayerState>()->CardsStack.Add(OwningPlayer->GetPlayerState<AMultiplayerState>()->CardsUsed[0]);
			OwningPlayer->GetPlayerState<AMultiplayerState>()->CardsUsed.Remove(Cast<APlayers>(OwningPlayer)->GetPlayerState<AMultiplayerState>()->CardsStack.Last());
		}
	}
	
	int CountCardsInHands = 1;
	
	if (NewCards)
	{
		CountCardsInHands = OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards.Num();
	}

	for (int i = CountCardsInHands; i < Count + CountCardsInHands; i++)
	{
		if (NewCards)
		{
			OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards.Add(Cast<APlayers>(OwningPlayer)->GetPlayerState<AMultiplayerState>()->CardsStack[0]);
            Cast<APlayers>(OwningPlayer)->GetPlayerState<AMultiplayerState>()->CardsStack.Remove(OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards[i]);
		}
		
		OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards[0]->ServerMoveActor(Hand->GetComponentLocation());
        OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards[0]->ServerRotateActor(Hand->GetComponentRotation());
		
		if (OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards.Num() >= 2)
		{
			FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
            OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards[i]->AttachToActor(OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards[i - 1], TransformRules, "CardSocket");
		}
		
		OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards[0]->ServerRotateActor(FRotator(OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards[0]->GetActorRotation().Pitch - 2.0f * (OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards.Num() - 1) * 2, OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards[0]->GetActorRotation().Yaw + 2.0f * (OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards.Num() - 1), OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards[0]->GetActorRotation().Roll));
		// OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards[0]->ServerMoveActor(FVector(OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards[0]->GetActorLocation().X, OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards[0]->GetActorLocation().Y - 7.f * (OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards.Num() - 1), OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards[0]->GetActorLocation().Z));
		OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards[0]->ServerMoveActor(OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards[0]->GetActorLocation() + OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards[0]->GetActorForwardVector() * 8.f * (OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards.Num() - 1));
	}
	
	if (OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards.Num() == 1)
	{
		OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards[0]->ServerMoveActor(Hand->GetComponentLocation());
		OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards[0]->ServerRotateActor(Hand->GetComponentRotation());
	}
	
	OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards[0]->ServerRotateActor(FRotator(OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards[0]->GetActorRotation().Pitch, OwningPlayer->GetPlayerState<AMultiplayerState>()->HandCards[0]->GetActorRotation().Yaw, Hand->GetComponentRotation().Roll + 50.f));
}

void AExpeditionPlate::TakeSunCards(AActor* ChooseActor)
{
	bool bCardsExist = false;
	
	if (Cast<ACards>(ChooseActor))
	{
			OwningPlayer->GetPlayerState<AMultiplayerState>()->CardsUsed.Add(Cast<ACards>(ChooseActor));
        	Market->SunCards.Remove(Cast<ACards>(ChooseActor));  
	}
	
	for (int i = 0; i < Market->SunCards.Num(); i++)
	{
		if (ChooseActor->GetName().Mid(3, ChooseActor->GetName().Len() - 7) == Market->SunCards[i]->GetName().Mid(3, Market->SunCards[i]->GetName().Len() - 7))
		{
			bCardsExist = true;
		}
	}
	if (!bCardsExist)
	{
		for (int a = 0; a < Market->Places.Num(); a++)
		{
			if (Market->Places[a]->GetComponentLocation() == ChooseActor->GetActorLocation())
			{
				EmptyPlaces.AddUnique(Market->Places[a]);
			}
		}
	}
	
	TOUSED(Cast<ACards>(ChooseActor))
}

void AExpeditionPlate::ServerSpawnCard_Implementation(TSubclassOf<AActor> Card)
{
	OwningPlayer->GetPlayerState<AMultiplayerState>()->CardsStack.Add(GetWorld()->GetAuthGameMode()->GetWorld()->SpawnActor<ACards>(Card));
}
