#include "Players.h"

#include "Expeditioner.h"
#include "ExpeditionPlate.h"
#include "EngineUtils.h"
// #include "Market.h"
#include "Blueprint/UserWidget.h"
#include "TheQuestforElDorado/GameStates/MultiplayerGameState.h"
#include "TheQuestforElDorado/Includes/Define.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Runtime/Core/Tests/Containers/TestUtils.h"
#include "TheQuestforElDorado/HUD/MainMenu.h"
#include "TheQuestforElDorado/PlayerState/MultiplayerState.h"

APlayers::APlayers()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
}

void APlayers::BeginPlay()
{
	Super::BeginPlay();
	
	Menu = CreateWidget<UMainMenu>(GetWorld(), MenuClass);
	Menu->AddToViewport();
	
	if (GetWorld()->GetFirstPlayerController())
	{
		GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	}
	
	// GameState = GetWorld()->GetGameState<AMultiplayerGameState>();
	
	// for (TActorIterator<AMarket> It(GetWorld()); It;)
	// {
	// 	Market = *It;
	// 	break;
	// }
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), TargetPoints);
	
	// Test::Shuffle(Barriers);
	
	// for (const AActor* It : TargetPoints)
	// {
	// 	if (!It->Tags[0].ToString().Contains("Barriers")) continue;
	// 	GetWorld()->GetAuthGameMode()->GetWorld()->SpawnActor<AActor>(Barriers[FCString::Atoi(*It->Tags[0].ToString().Mid(8, 1)) - 1], It->GetActorLocation(), It->GetActorRotation(), FActorSpawnParameters());
	// }
}

void APlayers::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (GetWorld()->GetMapName().Contains("Map") and Menu->IsInViewport())
	{
	 	Menu->RemoveFromParent();
	 		
	 	if (GetWorld()->GetFirstPlayerController())
	 	{
	 		GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
	 		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
		}
	}
	
	SpawnPlatesAndExpeditioners();
	
}

void APlayers::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ThisClass::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ThisClass::MoveRight);
	PlayerInputComponent->BindAxis("MoveUp", this, &ThisClass::MoveUp);
	PlayerInputComponent->BindAxis("LookUp", this, &ThisClass::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &ThisClass::Turn);
	
	PlayerInputComponent->BindAction("Choose", IE_Pressed, this, &ThisClass::Choose);
	PlayerInputComponent->BindAction("EndTurn", IE_Pressed, this, &ThisClass::EndTurn);
	PlayerInputComponent->BindAction("ToPlate", IE_Pressed, this, &ThisClass::ToPlate);
	PlayerInputComponent->BindAction("ToExpeditioner", IE_Pressed, this, &ThisClass::ToExpeditioner);
	PlayerInputComponent->BindAction("ToMarket", IE_Pressed, this, &ThisClass::ToMarket);
}

void APlayers::SpawnPlatesAndExpeditioners()
{
	if (Expeditioners.IsEmpty() or Plates.IsEmpty() or Barriers.IsEmpty()) return;
	if (!GetWorld()->GetMapName().Contains("Map") or !HasAuthority() or !GetPlayerState<AMultiplayerState>()) return;
	Menu->RemoveFromParent();
	if (Players.Num() >= 4) return;
	
	Players.AddUnique(this);
	for (TActorIterator<APlayers> It1(GetWorld()); It1; ++It1)
	{
		if (It1->bInMatch) continue;
		Players.AddUnique(*It1);
		for (const AActor* It : TargetPoints)
		{
			if (!It->Tags[0].ToString().Contains("Plate") and !It->Tags[0].ToString().Contains("Expeditioner")) continue;
			if (!It->Tags[0].ToString().Contains(FString::FromInt(Players.Find(*It1)))) continue;
			
			if (It->Tags[0].ToString().Contains("Plate"))
			{
				for (int i = 0; i < 4; i++)
				{
					if (Plates[i]->GetName().Contains(Colors[Players.Find(*It1)]))
					{
						if (Players.Num() == 1)
						{
							It1->GetPlayerState<AMultiplayerState>()->Plate = GetWorld()->GetAuthGameMode()->GetWorld()->SpawnActor<AExpeditionPlate>(Plates[i], It->GetActorLocation(), It->GetActorRotation(), FActorSpawnParameters());
							It1->GetPlayerState<AMultiplayerState>()->Plate->CreateCards(this);
							It1->GetPlayerState<AMultiplayerState>()->Plate->SetOwner(Cast<APlayerController>(It1->GetController()));
						}

					}
				}
			}
			if (It->Tags[0].ToString().Contains("Expeditioner"))
			{
				for (int i = 0; i < 4; i++)
				{
					if (Expeditioners[i]->GetName().Contains(Colors[Players.Find(*It1)]))
					{
						It1->GetPlayerState<AMultiplayerState>()->Expeditioner = GetWorld()->GetAuthGameMode()->GetWorld()->SpawnActor<AExpeditioner>(Expeditioners[i], It->GetActorLocation(), It->GetActorRotation(), FActorSpawnParameters());
						It1->GetPlayerState<AMultiplayerState>()->Expeditioner->SetOwner(Cast<APlayerController>(It1->GetController()));
					}
				}
			}
			It1->bInMatch = true;
			
		}
	}
}

void APlayers::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void APlayers::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void APlayers::MoveUp(float Value)
{
	AddMovementInput(FVector(0.f,0.f,1.f), Value);
}

void APlayers::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void APlayers::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void APlayers::Choose()
{
	if (!GetPlayerState<AMultiplayerState>()) return;
	if (GetPlayerState<AMultiplayerState>()->Expeditioner)
	{
		GetPlayerState<AMultiplayerState>()->Expeditioner->MoveToField(this);
	}
	if (GetPlayerState<AMultiplayerState>()->Plate)
	{
		GetPlayerState<AMultiplayerState>()->Plate->ChooseCards(this);
	}
}

void APlayers::EndTurn()
{
	if (!GetPlayerState<AMultiplayerState>()) return;
	if (GetPlayerState<AMultiplayerState>()->Plate)
	{
		GetPlayerState<AMultiplayerState>()->Plate->EndTurn(this);
	}
}

void APlayers::ToExpeditioner()
{
	// if (Expeditioner)
	// {
	// 	SetActorLocation(Expeditioner->CameraPlace->GetComponentLocation());
	// 	SetActorRotation(Expeditioner->CameraPlace->GetComponentRotation());
	// }
}

void APlayers::ToPlate()
{
	// if (Plate)
	// {
	// 	SetActorLocation(Plate->CameraPlace->GetComponentLocation());
	// }
}

void APlayers::ToMarket()
{
	// if (Market)
	// {
	// 	SetActorLocation(Market->CameraPlace->GetComponentLocation());
	// 	SetActorRotation(Market->CameraPlace->GetComponentRotation());
	// }
}
